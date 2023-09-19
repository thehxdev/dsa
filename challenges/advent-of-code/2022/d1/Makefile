CC := gcc
CFLAGS := -std=gnu17 -Wall -Wextra -Wshadow -pedantic -Wfatal-errors
CFLAGS += -Wno-unused-result
CFLAGS += -ggdb -Og
# CFLAGS += -O3

SRC_DIR := ./src

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
BIN := a.out


$(BIN): $(OBJ_FILES)
	$(CC) -o $(BIN) $(wildcard $(SRC_DIR)/*.o)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$*.c

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o

check:
	valgrind --leak-check=full ./$(BIN) input
