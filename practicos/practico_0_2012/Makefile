CC = g++
CFLAGS = -g -Wall -w --std=c++17 -Os

INCLUDE_DIR = include
SRC_DIR = src
BIN_DIR = bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp)

all: main vector_operations

main: main.cpp
	@echo "Compiling main.cpp"
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -o $(BIN_DIR)/main main.cpp $(SRC_FILES)

main: vector_operations.cpp
	@echo "Compiling vector_operations.cpp"
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -o $(BIN_DIR)/vector_operations vector_operations.cpp $(SRC_FILES)

clean:
	@echo " Cleaning..."
	$(RM) $(BIN_DIR)*
