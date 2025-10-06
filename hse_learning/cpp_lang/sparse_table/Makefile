CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++17
PATH_TO_INCLUDE=./include

all: build build/run

build:
	@mkdir -p build

run: build/run
	@printf "Running executable\n"
	@./build/run

build/run: build/main.o
	@printf "Compilation is successful\n"
	@$(CC) build/main.o -o build/run
	@printf "Linking is successful\n"

build/main.o: src/main.cpp
	@$(CC) $(CFLAGS) -I $(PATH_TO_INCLUDE) -c src/main.cpp -o build/main.o

clean:
	@printf "Cleaning successful\n"
	@rm -rf build

.PHONY: run clean