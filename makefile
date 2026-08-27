# Copyright (C) 2026 Devin Shwagginz

CRYSTAL_FLAGS := -DRANGECHECK -DPRECOMPUTED
EXEC := doo-cr


CURRENT_DIR := $(CURDIR)

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
	RLMAKE := cmake --build . --config Release
	AMMAKE := cmake --build .
	RLOUT := libraylib.dll
	AMOUT := libADLMIDI.dll
	CHANGE_LIB_NAMES := 
else ifeq ($(DETECTED_OS),Linux)
	LIB_EXT := so
	RLMAKE := make -Bj4 SHARED_RAYLIB=YES PLATFORM=PLATFORM_DESKTOP
	AMMAKE := make
	RLOUT := libraylib.so.6.0.0
	AMOUT := libADLMIDI.so.1.6.3
	CHANGE_LIB_NAMES := patchelf --replace-needed libADLMIDI.$(LIB_EXT).1 ./libADLMIDI.$(LIB_EXT) ./bin/$(EXEC) && patchelf --replace-needed libraylib.$(LIB_EXT).600 ./libraylib.$(LIB_EXT) ./bin/$(EXEC) && patchelf --replace-needed libcvars.$(LIB_EXT) ./libcvars.$(LIB_EXT) ./bin/$(EXEC)
else ifeq ($(DETECTED_OS),macOS)
	LIB_EXT := dylib
	RLMAKE := make -Bj4 SHAREDLIBS="-lglfw -framework OpenGL -framework OpenAL -framework Cocoa" SHARED_RAYLIB=YES PLATFORM=PLATFORM_DESKTOP
	AMMAKE := make
	RLOUT := libraylib.6.0.0.dylib
	AMOUT := libADLMIDI.1.6.3.dylib
	CHANGE_LIB_NAMES := install_name_tool -change "@rpath/libADLMIDI.1.$(LIB_EXT)" "./libADLMIDI.$(LIB_EXT)" ./bin/$(EXEC) && install_name_tool -change "@rpath/libraylib.600.$(LIB_EXT)" "./libraylib.$(LIB_EXT)" ./bin/$(EXEC)
endif


.PHONY: all clean
all: libcvars.$(LIB_EXT) libraylib.$(LIB_EXT) libADLMIDI.$(LIB_EXT)
	test -d bin || mkdir bin && \
	shards install
	shards update
	crystal build src/doo-cr.cr $(CRYSTAL_FLAGS) -o bin/$(EXEC) --link-flags="-L$(CURRENT_DIR) -LC:/msys64/clangarm64/lib"
	mv -f libcvars.$(LIB_EXT) ./bin
	cp -f libraylib.$(LIB_EXT) ./bin
	cp -f libADLMIDI.$(LIB_EXT) ./bin
	$(CHANGE_LIB_NAMES)
	
clean:
	rm -rf raylib
	rm -rf libADLMIDI
	rm -rf bin
	rm libraylib.$(LIB_EXT)
	rm libADLMIDI.$(LIB_EXT)


libcvars.$(LIB_EXT):
	cc -shared -fPIC -x c \
		-Wl,-undefined,dynamic_lookup \
		-DDOOM_IMPLEMENTATION \
			./src/cvars.h -o libcvars.$(LIB_EXT)

libraylib.$(LIB_EXT):
	test -d raylib || git clone --depth 1 --branch 6.0 --recursive https://github.com/raysan5/raylib 
	sed -i.bak 's/^    #define SUPPORT_SCREEN_CAPTURE          1/\/\/    #define SUPPORT_SCREEN_CAPTURE          1/' raylib/src/config.h
	cd raylib && \
	test -d build || mkdir build && \
	cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_POLICY_VERSION_MINIMUM="3.5" && \
	$(RLMAKE) && \
	cp ./raylib/$(RLOUT) ../../libraylib.$(LIB_EXT)

libADLMIDI.$(LIB_EXT):
	test -d libADLMIDI || git clone https://github.com/Wohlstand/libADLMIDI
	cd libADLMIDI && \
	test -d build || mkdir build && \
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release -DlibADLMIDI_SHARED=ON .. && \
	$(AMMAKE) && \
	cp ./$(AMOUT) ../../libADLMIDI.$(LIB_EXT)


