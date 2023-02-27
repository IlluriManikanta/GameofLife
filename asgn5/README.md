# Assignment 5 - Public Key Cryptography

The program will be implementing a encryt and decrypt file that will take an inputfile and will encrypt the contents and decrypt using the ss library. 

## Files In The Repository
Keygen.c
Encrypt.c
Decrypt,c
Numtheroy.c
Numtheory.h
Randstad.c
Randstate.h
 ss .c
 ss .h
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
Then run ./encrypt with flag of choice as mentioned in the below section. Then enter the file name of the file that you would like to encrypt. Then add -o flag with the outputfile name and add -v flag. 

Then run ./decrypt with flag of choice as mentioned in the below section. Then enter the file name of the file that you would like to decrypt. Then add -o flag with the final outputfile name and add -v flag. 


### Flags

• -i : specifies the input file to encrypt (default: stdin). 
• -o : specifies the output file to encrypt (default: stdout). 
• -n : specifies the file containing the public key (default:  ss .pub). 
• -v : enables verbose output. 
• -h : displays program synopsis and usage

