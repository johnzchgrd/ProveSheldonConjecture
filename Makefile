#TODO:
#     fvisibility
#     versionscript
CC := gcc
Verbose := false
#Verbose
export CMD_PREFIX := @
ifeq ($(Verbose),true)
	CMD_PREFIX :=
endif

# default as DEBUG mode
# Build and output paths
debug: export BINARY_PATH := bin/debug/
debug: export BIN_NAME := main
debug: export SO_NAME := sheldon
debug: export BUILD_PATH := build/debug
debug: export BIN_PATH := bin/debug
debug: export LIB_NAME := lib$(SO_NAME).so
release: export BINARY_PATH := bin/release/
release: export BIN_NAME := main
release: export SO_NAME := sheldon
release: export LIB_NAME := lib$(SO_NAME).so
release: export BUILD_PATH := build/release
release: export BIN_PATH := bin/release

debug: mkdirs
#make lib
	$(CMD_PREFIX)make -C lib debug
	$(CMD_PREFIX)cp lib/$(BIN_PATH)/$(LIB_NAME) $(BINARY_PATH)$(LIB_NAME)
#make src
	$(CMD_PREFIX)make -C src debug
	$(CMD_PREFIX)cp src/$(BIN_PATH)/$(BIN_NAME) $(BINARY_PATH)$(BIN_NAME)

release: mkdirs
#make lib
	$(CMD_PREFIX)make --no-print-directory -C lib release
	$(CMD_PREFIX)cp lib/$(BIN_PATH)/$(LIB_NAME) $(BINARY_PATH)$(LIB_NAME)
#make src
	$(CMD_PREFIX)make --no-print-directory -C src release
	$(CMD_PREFIX)cp src/$(BIN_PATH)/$(BIN_NAME) $(BINARY_PATH)$(BIN_NAME)

.PHONY:mkdirs
mkdirs:
	@echo "Creating directories $(BINARY_PATH)"
	@mkdir -p $(BINARY_PATH)

.PHONY:clean
clean:
	-$(CMD_PREFIX)make --no-print-directory -C src clean
	-$(CMD_PREFIX)make --no-print-directory -C lib clean

cleanall:clean
	-$(CMD_PREFIX)rm -r -f bin

.PHONY:cleansrc
cleansrc:
	-$(CMD_PREFIX)rm -r -f src/bin src/build

.PHONY:drebuild
drebuild:
	-$(CMD_PREFIX)make --no-print-directory -C src clean
	-$(CMD_PREFIX)rm -f tmp/*.tmp
	-$(CMD_PREFIX)make --no-print-directory debug -j