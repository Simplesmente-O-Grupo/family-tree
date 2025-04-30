#A loucura ainda está por vir.

CC=gcc

CFLAGS=-g -Wextra -Wall -Werror 

ftree: main.o
	$(CC) ${CFLAGS} $^ -o $@

main.o: src/main.c
	$(CC) -c $< -o $@


.PHONY: clean
clean:
	rm -v main.o ftree
