# Minimal portable Makefile for g++
CXX ?= g++
JOBS ?= 10
SRC_DIR ?= src
BUILD_DIR ?= build
BIN_DIR ?= bin
TARGET ?= app
STD ?= -std=c++17
WARN ?= -Wall -Wextra

# Find sources: include files in SRC_DIR if it exists, plus any .cpp in top-level directory
ifeq ("$(wildcard $(SRC_DIR))","")
SRCS := $(wildcard *.cpp)
else
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp) $(wildcard *.cpp)
endif

# If still empty, produce a helpful error later
ifeq ($(strip $(SRCS)),)
HAS_SRCS := 0
else
HAS_SRCS := 1
endif

# Convert source paths to object paths under BUILD_DIR
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

MODE ?= release
ifeq ($(MODE),debug)
CXXFLAGS := -g -O0 $(STD) $(WARN)
LDFLAGS :=
else ifeq ($(MODE),profile)
CXXFLAGS := -g -O2 -pg $(STD) $(WARN)
LDFLAGS := -pg
else
CXXFLAGS := -O3 $(STD) $(WARN)
LDFLAGS :=
endif

.PHONY: help all clean distclean dirs run_parallel debug release profile

.DEFAULT_GOAL := run_parallel

# Check compiler availability at start
ifeq ($(shell command -v $(CXX) 2>/dev/null || true),)
CXX_MISSING := 1
else
CXX_MISSING := 0
endif


.PHONY: run
run: all
	@echo "Running $(BIN_DIR)/$(TARGET)"
	@$(BIN_DIR)/$(TARGET)

run_parallel:
ifeq ($(CXX_MISSING),1)
	@echo "Error: '$(CXX)' not found. Install g++ or set CXX to your compiler (e.g. CXX=clang++)." >&2
	@exit 1
endif
ifeq ($(HAS_SRCS),0)
	@echo "Error: no .cpp source files found. Place sources in '$(SRC_DIR)/' or the project root." >&2
	@exit 1
endif
ifneq (,$(findstring -j,$(MAKEFLAGS)))
	@$(MAKE) all
else
	@echo "Re-running make with -j$(JOBS) (MODE=$(MODE))"
	@$(MAKE) -j$(JOBS) MODE=$(MODE) all
endif

all: dirs $(BIN_DIR)/$(TARGET)

# Link
$(BIN_DIR)/$(TARGET): $(OBJS)
	@echo "Linking -> $@"
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Generic compile rule: preserve directories
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Support sources found under nested src/ paths
# If SRCS contains src/foo/bar.cpp, transform to build/src/foo/bar.o
# The pattern rule above handles top-level; add a secondary rule:
$(BUILD_DIR)/%/%.o: %/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

debug:
	@$(MAKE) MODE=debug -j$(JOBS) all

release:
	@$(MAKE) MODE=release -j$(JOBS) all

profile:
	@$(MAKE) MODE=profile -j$(JOBS) all

clean:
	@echo "Removing build artifacts"
	@rm -rf $(BUILD_DIR) $(BIN_DIR)/$(TARGET)

distclean: clean
	@echo "Done."



help:
	@echo ""
	@echo "Usage: make [target] [VARIABLE=value]"
	@echo ""
	@echo "Targets:"
	@echo "  help      Show this help"
	@echo "  all       Build project (default)"
	@echo "  debug     Build in debug mode"
	@echo "  release   Build in release mode"
	@echo "  profile   Build with profiling"
	@echo "  clean     Remove build artifacts"
	@echo ""
	@echo "Variables:"
	@echo "  CXX       C++ compiler (default: g++)"
	@echo "  JOBS      Parallel jobs when make re-invokes itself (default: 10)"
	@echo "  MODE      Build mode: debug, release, profile (default: release)"
	@echo "  SRC_DIR   Source dir (default: src)"
	@echo "  BUILD_DIR Build dir (default: build)"
	@echo "  BIN_DIR   Output dir (default: bin)"
	@echo "  TARGET    Output binary name (default: app)"
	@echo ""
