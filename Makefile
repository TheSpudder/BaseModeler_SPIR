# Compiler and flags
CC := gcc
CFLAGS := -ggdb -Wall -Werror -O -std=c99 -D_DEFAULT_SOURCE
LDFLAGS := -lm

# Core source file
SRC := src/base.c
OBJ := $(SRC:.c=.o)

# Tests
# Add test names here (without .c)
MYTESTS := test_test_dbm_to_watts test_test_watts_to_dbm test_test_fspl test_test_log_distance test_test_alpha_beta

# Default rule: just make sure base.c compiles
all: $(OBJ)

# Run all tests
test: $(MYTESTS)
	@echo
	@for t in $(MYTESTS); do \
	    printf "running %-30s ... " $$t; \
	    ./$$t; \
	done
	@echo

# Build a test executable
# test_foo → tests/foo.c + base.o
test_%: tests/%.o $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile any .c into .o
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean build artifacts
clean:
	rm -f src/*.o tests/*.o $(MYTESTS)

.PHONY: all test clean
