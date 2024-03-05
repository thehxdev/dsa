CC := gcc
CFLAGS := -std=c17 -Wall -Wextra
CFLAGS += -Wno-unused-result
CFLAGS += -ggdb -Og

SRC_DIR :=./src

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
BIN := a.out


$(BIN): $(OBJ_FILES)
	$(CC) -o $(BIN) $(OBJ_FILES)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o

check:
	valgrind ./$(BIN)

checkfull:
	valgrind --leak-check=full ./$(BIN)
