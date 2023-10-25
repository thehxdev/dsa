CC := gcc
CFLAGS := -std=gnu17 -Wall -Wextra
CFLAGS += -Wno-unused-result
# CFLAGS += -O3
CFLAGS += -ggdb -Og
LIBS :=

SRC_DIR :=./src

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
BIN := a.out


$(BIN): $(OBJ_FILES)
	$(CC) -o $(BIN) $(OBJ_FILES) $(LIBS)

%.o: $(SRC_DIR)/%.c
	$(CC) -c $(SRC_DIR)/$*.c $(CFLAGS) $(LIBS)

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o

check:
	valgrind ./$(BIN) input

checkfull:
	valgrind --leak-check=full ./$(BIN) input
