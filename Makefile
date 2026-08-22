CXX      := c++
CXXFLAGS := -std=c++17 -Wall -Wextra

DEBUG_FLAGS   := -g -O0
RELEASE_FLAGS := -O3 -DNDEBUG

SRC      := $(wildcard src/*/*.cpp)
TEST_SRC := test/test_matrix.cpp

DEBUG_BIN   := test/test_matrix_debug
RELEASE_BIN := test/test_matrix_release

.PHONY: all debug release test test-debug test-release clean

all: debug release

debug: $(DEBUG_BIN)

release: $(RELEASE_BIN)

$(DEBUG_BIN): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -Isrc -Itest $^ -o $@

$(RELEASE_BIN): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -Isrc -Itest $^ -o $@

test: test-debug test-release

test-debug: $(DEBUG_BIN)
	./$(DEBUG_BIN)

test-release: $(RELEASE_BIN)
	./$(RELEASE_BIN)

clean:
	rm -f $(DEBUG_BIN) $(RELEASE_BIN)
