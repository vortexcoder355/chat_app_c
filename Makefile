# Makefile for Chat Application (Server and Client)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SERVER_SRC = $(SRC_DIR)/chat_server.c
CLIENT_SRC = $(SRC_DIR)/chat_client.c

# Object files
SERVER_OBJ = $(OBJ_DIR)/chat_server.o
CLIENT_OBJ = $(OBJ_DIR)/chat_client.o

# Executables
SERVER_BIN = $(BIN_DIR)/chat_server
CLIENT_BIN = $(BIN_DIR)/chat_client

# Targets

# Default target
all: $(SERVER_BIN) $(CLIENT_BIN)

# Build server binary
$(SERVER_BIN): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Build client binary
$(CLIENT_BIN): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile the server source into an object file
$(OBJ_DIR)/chat_server.o: $(SRC_DIR)/chat_server.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the client source into an object file
$(OBJ_DIR)/chat_client.o: $(SRC_DIR)/chat_client.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object and binary files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the server
run-server: $(SERVER_BIN)
	./$(BIN_DIR)/chat_server

# Run the client
run-client: $(CLIENT_BIN)
	./$(BIN_DIR)/chat_client

.PHONY: all clean run-server run-client
