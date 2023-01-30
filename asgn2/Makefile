#Got make file from millers class Fall 2022, I didnt not write this, all credit belongs to miller's


EXECBIN  = mathlib-test

CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra
LIBFLAGS = -lm


SOURCES  = $(wildcard *.c)

OBJECTS  = $(SOURCES:%.c=%.o)


.PHONY: all clean


all: $(EXECBIN)


$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFLAGS)


clean:
	rm -f $(EXECBIN) $(OBJECTS)
	
format:
	clang-format -i -style=file *.[ch]


%.o : %.c
	$(CC) $(CFLAGS) -c $<


