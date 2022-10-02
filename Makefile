DRIVER        := lib/snake_main.cpp
GTEST         := googletest
TEST          := snake_helper_test.cpp
HEADERS       := lib/snake.h snake_helper.h lib/snake_logic.h
IMPLEMS       := snake_helper.cpp lib/snake_logic.cpp
FILES         := $(DRIVER) $(HEADERS) $(IMPLEMS) $(TEST)
TEST_OUT      := test
OUT           := snake
FLAGS         := -Wall -Werror -Wno-unused-function

.PHONY: format build test all clean

all: format build test

format:
	@echo "\n========================\nFormatting files\n========================\n"
	@clang-format $(FILES) -i -style=google -verbose
	@echo "\n========================\nFormatting complete\n========================\n"

build: $(DRIVER) $(HEADERS) $(IMPLEMS)
	@echo "\n========================\nCompiling Snake\n========================\n"
	@g++ -std=c++17 $(IMPLEMS) $(DRIVER) $(FLAGS) -o $(OUT) -lncurses
	@echo "========================\nCompilation complete\nRun your code with ./$(OUT)\n========================\n"

test:
	@echo "\n========================\nRunning tests\n========================\n"
	@g++ -std=c++17 $(IMPLEMS) $(TEST) $(GTEST)/libgtest.a $(GTEST)/libgtest_main.a -isystem $(GTEST)/include -pthread -o $(TEST_OUT)
	@./$(TEST_OUT)
	@echo "\n========================\nTests complete\n========================\n"

clean:
	@rm -f $(OUT) $(TEST_OUT)
