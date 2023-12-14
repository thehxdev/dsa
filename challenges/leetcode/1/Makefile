CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Wno-unused-result
SRC_FILES := $(wildcard ./*.c)
BIN := a.out


$(BIN):
	$(CC) $(CFLAGS) -o $(BIN) $(SRC_FILES)

clean:
	rm -rf $(BIN)
