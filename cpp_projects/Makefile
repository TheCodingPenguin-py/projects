# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g

# Default: if you run `make` with no args, print usage
.DEFAULT_GOAL := help

# Compile a single file: use `make filename` (no .cpp)
# Example: `make hello` will compile hello.cpp -> hello
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean: remove all executables in the current directory that match compiled patterns
.PHONY: clean help
clean:
	@echo "Removing executables..."
	@for f in *; do \
	  if [ -x "$$f" ] && [ -f "$$f" ] && file "$$f" | grep -q "executable"; then \
	    echo "  rm $$f"; rm -f "$$f"; \
	  fi; \
	done

help:
	@echo "Usage:"
	@echo "  make <name>    Compile <name>.cpp to executable <name>"
	@echo "  make clean     Remove executables in this directory"
