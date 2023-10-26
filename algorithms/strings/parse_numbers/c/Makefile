CC := gcc
CFLAGS := -std=gnu17 -Wall -Wextra -Wshadow
CFLAGS += -Werror -Wno-unused-result
CFLAGS += -ggdb -Og
LIBS := -lm

SRC_DIR := ./src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
BIN := a.out


$(BIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ_FILES) $(LIBS)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(LIBS)

clean:
	rm -rf $(SRC_DIR)/*.o $(BIN)
