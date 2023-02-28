CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 


all: encode decode

trie: trie.o
	$(CC) -o $@ $^ $(LFLAGS)
	
word: word.o
	$(CC) -o $@ $^ $(LFLAGS)
	
io: io.o 
	$(CC) -o $@ $^ $(LFLAGS)
	
encode: encode.o tire.o word.o io.o 
	$(CC) -o $@ $^ $(LFLAGS)

decode: decode.o tire.o word.o io.o 
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f keygen encrypt decrypt *.o

format:
	clang-format -i -style=file *.[ch]

