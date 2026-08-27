# Copyright (C) 2026 Devin Shwagginz

CRYSTAL_FLAGS := --release --no-debug -DRANGECHECK -DPRECOMPUTED
EXEC := doo-cr
OUTDIR := ./bin

# Freedoom is free/libre game data that can be used with this source port.
FREEDOOM_VERSION ?= 0.13.0
FREEDOOM_URL := https://github.com/freedoom/freedoom/releases/download/v$(FREEDOOM_VERSION)/freedoom-$(FREEDOOM_VERSION).zip
FREEDM_URL := https://github.com/freedoom/freedoom/releases/download/v$(FREEDOOM_VERSION)/freedm-$(FREEDOOM_VERSION).zip
FREEDOOM_ARCHIVE := .freedoom-$(FREEDOOM_VERSION).zip
FREEDM_ARCHIVE := .freedm-$(FREEDOOM_VERSION).zip

ifeq ($(OS),Windows_NT)
    # Windows-specific settings
    DETECTED_OS := Windows
		CURRENT_DIR := $(shell cygpath -m "$(CURDIR)")
		CRYSTAL_LIBRARY_PATH := $(shell crystal env CRYSTAL_EXEC_PATH)
else
    # Call uname on Unix-like environments
    UNAME_S := $(shell uname -s)
		CURRENT_DIR := $(CURDIR)
		CRYSTAL_LIBRARY_PATH := $(shell crystal env CRYSTAL_LIBRARY_PATH)
    ifeq ($(UNAME_S),Linux)
        DETECTED_OS := Linux
    endif
    ifeq ($(UNAME_S),Darwin)
        DETECTED_OS := macOS
    endif
endif

ifeq ($(DETECTED_OS),Windows)
	LIB_EXT := dll
	AMMAKE := cmake --build .
	AMOUT := libADLMIDI.dll
	CRYSTAL_LIBS := libiconv-2.dll libgc-1.dll libwinpthread-1.dll
	ADL_RUNTIME := libADLMIDI.dll
	LIBCVARS_FLAGS := -shared -x c
	PLATFORM_LINK_FLAGS := -L$(CURRENT_DIR)
else ifeq ($(DETECTED_OS),Linux)
	LIB_EXT := so
	AMMAKE := make
	AMOUT := libADLMIDI.so.1.6.3
	CRYSTAL_LIBS :=
	ADL_RUNTIME := libADLMIDI.so.1
	LIBCVARS_FLAGS := -shared -fPIC -x c
	PLATFORM_LINK_FLAGS := -L$(CURRENT_DIR) -Wl,-rpath,\$${ORIGIN}
else ifeq ($(DETECTED_OS),macOS)
	LIB_EXT := dylib
	AMMAKE := make
	AMOUT := libADLMIDI.1.6.3.dylib
	CRYSTAL_LIBS :=
	ADL_RUNTIME := libADLMIDI.1.dylib
	LIBCVARS_FLAGS := -shared -fPIC -x c -Wl,-undefined,dynamic_lookup
	PLATFORM_LINK_FLAGS := -L$(CURRENT_DIR) -Wl,-rpath,@executable_path
endif

.PHONY: all clean doom-data
all: libcvars.$(LIB_EXT) libADLMIDI.$(LIB_EXT) $(addprefix $(OUTDIR)/,$(CRYSTAL_LIBS))
	mkdir -p $(OUTDIR)
	shards install
	crystal build src/doo-cr.cr $(CRYSTAL_FLAGS) -o $(OUTDIR)/$(EXEC) --link-flags='$(PLATFORM_LINK_FLAGS)'
	mv -f libcvars.$(LIB_EXT) $(OUTDIR)
	cp -f libADLMIDI.$(LIB_EXT) $(OUTDIR)/$(ADL_RUNTIME)

# Download and unpack the freely distributable Freedoom IWADs.
doom-data:
	@set -eu; \
	if test -s freedoom1.wad && test -s freedoom2.wad && test -s freedm.wad; then \
		echo "Freedoom data already exists."; \
	else \
		command -v curl >/dev/null || { echo "doom-data requires curl." >&2; exit 1; }; \
		command -v unzip >/dev/null || { echo "doom-data requires unzip." >&2; exit 1; }; \
		tmp_freedoom="$(FREEDOOM_ARCHIVE).tmp"; \
		tmp_freedm="$(FREEDM_ARCHIVE).tmp"; \
		trap 'rm -f "$$tmp_freedoom" "$$tmp_freedm"' 0; \
		curl --fail --location --retry 3 --output "$$tmp_freedoom" "$(FREEDOOM_URL)"; \
		unzip -j -o "$$tmp_freedoom" '*.wad' -d .; \
		curl --fail --location --retry 3 --output "$$tmp_freedm" "$(FREEDM_URL)"; \
		unzip -j -o "$$tmp_freedm" '*.wad' -d .; \
		echo "Freedoom data installed."; \
	fi
	
clean:
	rm -rf libADLMIDI
	rm -rf $(OUTDIR)
	rm -f libADLMIDI.$(LIB_EXT)


define COPY_LIB
$(OUTDIR)/$(1): $(CRYSTAL_LIBRARY_PATH)/$(1)
	test -d $(OUTDIR) || mkdir $(OUTDIR)
	cp -f "$(CRYSTAL_LIBRARY_PATH)/$(1)" "$(OUTDIR)/$(1)"
endef

$(foreach lib,$(CRYSTAL_LIBS),$(eval $(call COPY_LIB,$(lib)))) 


libcvars.$(LIB_EXT):
	cc $(LIBCVARS_FLAGS) \
		-DDOOM_IMPLEMENTATION \
			./src/cvars.h -o libcvars.$(LIB_EXT)

libADLMIDI.$(LIB_EXT):
	test -d libADLMIDI || git clone https://github.com/Wohlstand/libADLMIDI
	cd libADLMIDI && \
	test -d build || mkdir build && \
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release -DlibADLMIDI_SHARED=ON .. && \
	$(AMMAKE) && \
	cp ./$(AMOUT) ../../libADLMIDI.$(LIB_EXT)
