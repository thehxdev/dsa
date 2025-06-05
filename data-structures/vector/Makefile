CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wno-unused-result -ggdb -Og

SRC_DIR := ./src

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:.c=.o)
BIN := a.out


$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(OBJ)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o
