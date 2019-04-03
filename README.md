# SHA-256
Secure Hash Algorithm: A program written in C that calculates the SHA-256 checksum of an input.

This repository contains a file written in the programming language C called sha256.c. The author is Micheal Curley.

The objective of this assignment to implement the Secure Hash Algorithm (256-bit). In the end I'm getting the 256 output but the program is reading the bytes in the order of little endian whereas the outputs for specific files online is getting different outputs when tested due to the bytes being in the order of big endian.

Running the code

To run the code in this repository, the files must first be compiled so you will need a C compiler installed on your machine. Once that is installed, the code can be compiled and run by following these steps. We assume you are using the command line.

This program has to convert the order of bytes from little endian to big endian which means reversing the order of bits in the message.

Clone this repository using Git.
> git clone https://github.com/curley147/SHA-256.git
Change into the folder.
> cd SHA-256
Compile the first file with the following command.
> gcc -0 sha256 sha256.c
Run the executable produced followed by file name (I used testfile.txt as an example).
> ./sha256 testfile.txt
The program should output 8 64-bit integers in hexadecimal format

References

Endian conversion - "https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func"

Inline functions - "https://www.geeksforgeeks.org/inline-function-in-c/"

