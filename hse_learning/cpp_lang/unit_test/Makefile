CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++17
GTFLAGS=-lgtest -lgtest_main -lpthread
PATH_TO_GTEST=/wsl.localhost/Ubuntu/usr

all: build build/tests

build:
	@mkdir -p build

run: build/tests
	@printf "Running executable\n"
	@./build/tests

build/tests: build/qsort.o build/sort_tests.o build/main.o
	@printf "Compilation is successful\n"
	@$(CC) build/qsort.o build/sort_tests.o build/main.o -L $(PATH_TO_GTEST)/lib $(GTFLAGS) -o build/tests
	@printf "Linking is successful\n"

build/qsort.o: src/qsort.cpp
	@$(CC) $(CFLAGS) -I $(PATH_TO_GTEST)/include -c src/qsort.cpp -o build/qsort.o

build/sort_tests.o: src/sort_tests.cpp
	@$(CC) $(CFLAGS) -I $(PATH_TO_GTEST)/include -c src/sort_tests.cpp -o build/sort_tests.o

build/main.o: src/main.cpp
	@$(CC) $(CFLAGS) -I $(PATH_TO_GTEST)/include -c src/main.cpp -o build/main.o

clean:
	@printf "Cleaning successful\n"
	@rm -rf build

.PHONY: run clean