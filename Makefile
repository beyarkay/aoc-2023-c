CC = gcc
SRC_DIR = src
BIN_DIR = bin

# List of source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# List of targets (01, 02, ..., 25)
TARGETS = $(patsubst $(SRC_DIR)/%.c,%,$(SRC_FILES))

.PHONY: all clean $(TARGETS)

all: $(TARGETS)

# Build and run each target
run%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $< -o $(BIN_DIR)/$@
	./$(BIN_DIR)/$@

# Ensure the bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)
