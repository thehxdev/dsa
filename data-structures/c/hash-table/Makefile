CC :=gcc
CFLAGS := -std=c17 -Wall -Wextra
CFLAGS += -Wno-unused-result
CFLAGS += -ggdb -Og

SRC_DIR :=./src

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
OUT :=a.out


$(OUT): $(OBJ_FILES)
	$(CC) -o $(OUT) $(wildcard $(SRC_DIR)/*.o)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$*.c

clean:
	rm -rf $(OUT) $(SRC_DIR)/*.o

check:
	valgrind ./$(OUT)

checkfull:
	valgrind --leak-check=full ./$(OUT)
