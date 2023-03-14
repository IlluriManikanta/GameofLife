# Assignment 6 - Lempel-Ziv Compression
The program will be implementing a data compression method.  

## Files In The Repository
trie.c
word.c
io.c
trie.h
word.h
io.c
encode.c
decode.c
code.h
endian.h
Makefile
DESIGN.pdf
WRITEUP.pdf
README.md


# Make commands

First run: make clean

Then run: make format

Then run: make

## Running the program

Run the make command which will compile the files. 
Then run ./encode with flag of choice as mentioned in the below section. Then enter the file name of the file that you would like to encrypt. Then add -o flag with the outfile name and add -v flag. 

#Flags for encode
• -v : Print compression statistics to stderr.
 • -i : Specify input to compress (stdin by default) 
 • -o : Specify output of compressed input (stdout by default)


Then run ./decode with flag of choice as mentioned in the below section. Then enter the file name of the file that you would like to decrypt. Then add -o flag with the final outfile name and add -v flag.

#Flags for decode
• -v : Print decompression statistics to stderr.
 • -i : Specify input to decompress (stdin by default) 
• -o : Specify output of decompressed input (stdout by default) 





