CRYSTAL_FLAGS := -DRANGECHECK

ifeq ($(OS),Windows_NT)
    # Windows-specific settings
    DETECTED_OS := Windows
else
    # Call uname on Unix-like environments
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        DETECTED_OS := Linux
    endif
    ifeq ($(UNAME_S),Darwin)
        DETECTED_OS := macOS
    endif
endif

ifeq ($(DETECTED_OS),Windows)
	LIB_EXT := dll
else ifeq ($(DETECTED_OS),Linux)
	LIB_EXT := so
else ifeq ($(DETECTED_OS),macOS)
	LIB_EXT := dylib
endif


.PHONY: all clean
all: libpuredoom.$(LIB_EXT) libraylib.$(LIB_EXT) libADLMIDI.$(LIB_EXT)
	test -d bin || mkdir bin && \
	shards install
	crystal build src/doo-cr.cr $(CRYSTAL_FLAGS) --link-flags "-fuse-ld=/opt/homebrew/opt/lld/bin/ld64.lld" -o bin/libdoom
	mv -f libpuredoom.$(LIB_EXT) ./bin
	cp -f libraylib.$(LIB_EXT) ./bin
	cp -f libADLMIDI.$(LIB_EXT) ./bin
	install_name_tool -change "@rpath/libADLMIDI.1.$(LIB_EXT)" "./libADLMIDI.$(LIB_EXT)" ./bin/libdoom
	install_name_tool -change "@rpath/libraylib.600.$(LIB_EXT)" "./libraylib.$(LIB_EXT)" ./bin/libdoom

	cd ./bin && \
	./libdoom

clean:
	rm -rf raylib
	rm -rf libADLMIDI
	rm -rf bin
	rm libraylib.$(LIB_EXT)
	rm libADLMIDI.$(LIB_EXT)


libpuredoom.$(LIB_EXT):
	cc -shared -fPIC -x c \
		-Wl,-undefined,dynamic_lookup \
		-DDOOM_IMPLEMENTATION \
			PureDoom.h -o libpuredoom.$(LIB_EXT)

libraylib.$(LIB_EXT):
	test -d raylib || git clone --depth 1 --branch 6.0 --recursive https://github.com/raysan5/raylib 
	sed -i.bak 's/^    #define SUPPORT_SCREEN_CAPTURE          1/\/\/    #define SUPPORT_SCREEN_CAPTURE          1/' raylib/src/config.h
	cd raylib && \
	test -d build || mkdir build && \
	cd build && \
	cmake .. -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DBUILD_SHARED_LIBS=ON && \
	make -Bj4 SHAREDLIBS="-lglfw -framework OpenGL -framework OpenAL -framework Cocoa" SHARED_RAYLIB=YES PLATFORM=PLATFORM_DESKTOP && \
	cp ./raylib/libraylib.6.0.0.$(LIB_EXT) ../../libraylib.$(LIB_EXT)

libADLMIDI.$(LIB_EXT):
	test -d libADLMIDI || git clone https://github.com/Wohlstand/libADLMIDI
	cd libADLMIDI && \
	test -d build || mkdir build && \
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release -DlibADLMIDI_SHARED=ON .. && \
	make && \
	cp ./libADLMIDI.1.6.2.$(LIB_EXT) ../../libADLMIDI.$(LIB_EXT)


