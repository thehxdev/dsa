CC := gcc
CFLAGS := -std=c17 -Wall -Wextra
CFLAGS += -Wno-unused-result
CFLAGS += -ggdb -Og

SRC_DIR := ./src

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:.c=.o)
BIN := a.out


$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(wildcard $(SRC_DIR)/*.o)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$*.c

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o
