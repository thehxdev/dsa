CC=gcc
FLAGS=-Wall -Wextra -pedantic -std=c17
FLAGS+=-Werror
INPUT=main.c

default:
	$(CC) $(FLAGS) $(INPUT)

check:
	valgrind --leak-check=full ./a.out
