CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wno-unused-result -ggdb -Og

SRC_DIR :=./src

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
BIN := a.out


$(BIN): $(OBJ_FILES)
	$(CC) -o $(BIN) $(wildcard $(SRC_DIR)/*.o) $(CFLAGS) $(LIBS)

%.o: $(SRC_DIR)/%.c
	$(CC) -c $(SRC_DIR)/$*.c $(CFLAGS) $(LIBS)

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o

check:
	valgrind ./$(BIN) input

checkfull:
	valgrind --leak-check=full ./$(BIN) input
