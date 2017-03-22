CC = gcc
CFLAGS = -Wall -Werror -Wextra

sources = solution.c tree.c list.c commands.c
objects = $(sources:.c=.o)

solution: $(objects)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

solution.o: tree.h commands.h

commands.o: tree.h

tree.o: list.h

.PHONY: clean
clean:
	-rm $(objects) solution solution.gdb
