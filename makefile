.PHONY: all clean
all: libpuredoom.dylib libraylib.dylib libADLMIDI.dylib
	test -d bin || mkdir bin && \
	shards install
	crystal build src/libdoom-cr.cr --link-flags "-fuse-ld=/opt/homebrew/opt/lld/bin/ld64.lld" -o bin/libdoom
	mv -f libpuredoom.dylib ./bin
	cp -f libraylib.dylib ./bin
	cp -f libADLMIDI.dylib ./bin
	install_name_tool -change "@rpath/libADLMIDI.1.dylib" "./libADLMIDI.dylib" ./bin/libdoom
	install_name_tool -change "@rpath/libraylib.600.dylib" "./libraylib.dylib" ./bin/libdoom

	cd ./bin && \
	./libdoom

clean:
	rm -rf raylib
	rm -rf libADLMIDI
	rm -rf bin
	rm libraylib.dylib
	rm libADLMIDI.dylib


libpuredoom.dylib:
	cc -shared -fPIC -x c \
		-Wl,-undefined,dynamic_lookup \
		-DDOOM_IMPLEMENTATION \
			PureDoom.h -o libpuredoom.dylib

libraylib.dylib:
	test -d raylib || git clone --depth 1 --branch 6.0 --recursive https://github.com/raysan5/raylib 
	sed -i.bak 's/^    #define SUPPORT_SCREEN_CAPTURE          1/\/\/    #define SUPPORT_SCREEN_CAPTURE          1/' raylib/src/config.h
	cd raylib && \
	test -d build || mkdir build && \
	cd build && \
	cmake .. -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DBUILD_SHARED_LIBS=ON && \
	make -Bj4 SHAREDLIBS="-lglfw -framework OpenGL -framework OpenAL -framework Cocoa" SHARED_RAYLIB=YES PLATFORM=PLATFORM_DESKTOP && \
	cp ./raylib/libraylib.6.0.0.dylib ../../libraylib.dylib

libADLMIDI.dylib:
	test -d libADLMIDI || git clone https://github.com/Wohlstand/libADLMIDI
	cd libADLMIDI && \
	test -d build || mkdir build && \
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release -DlibADLMIDI_SHARED=ON .. && \
	make && \
	cp ./libADLMIDI.1.6.2.dylib ../../libADLMIDI.dylib


