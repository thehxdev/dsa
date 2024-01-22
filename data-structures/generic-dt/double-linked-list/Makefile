CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wno-unused-result
CFLAGS += -ggdb -Og
LIBS :=
# SANATIZE_FLAGS := -fsanitize=address -fno-omit-frame-pointer 
SANATIZE_FLAGS :=

SRC_DIR := ./src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
BIN := a.out


$(BIN): $(OBJ_FILES)
	$(CC) $(SANATIZE_FLAGS) -o $(BIN) $(OBJ_FILES)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(SRC_DIR)/*.o $(BIN)
