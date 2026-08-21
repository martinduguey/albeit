CXX      := c++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

SRC      := $(wildcard src/structures/*.cpp)
TEST_SRC := test/test_matrix.cpp
TEST_BIN := test/test_matrix

.PHONY: all test clean

all: $(TEST_BIN)

$(TEST_BIN): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -Iheader -Iutils $^ -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN)
