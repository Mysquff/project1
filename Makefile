CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEBUG_CFLAGS = -g $(CFLAGS)

sources = solution.c tree.c list.c commands.c parse.c
objects = $(sources:.c=.o)
debug_objects = $(sources:.c=.do)

solution: $(objects)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.do: %.c
	$(CC) -c $(DEBUG_CFLAGS) -o $@ $<

solution.o solution.do: tree.h commands.h parse.h

commands.o commands.do: tree.h commands.h

tree.o tree.do: list.h tree.h

parse.o parse.do: tree.h parse.h

.PHONY: all
all: solution debug

.PHONY: debug
debug: $(debug_objects)
	$(CC) -o solution.dbg $^

.PHONY: clean
clean:
	-rm -f $(objects) $(debug_objects) solution solution.dbg
