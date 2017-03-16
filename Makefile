CFLAGS = -Wall -Werror -Wextra

sources = solution.c tree.c list.c
objects = $(sources:.c=.o)

solution: $(objects)
	cc -o $@

%.o: %.c
	cc $CFLAGS -o $@ $<

solution.o: tree.h

tree.o: list.h

.PHONY: clean
clean:
	-rm $(objects) solution solution.gdb
