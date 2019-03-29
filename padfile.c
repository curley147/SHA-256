// Micheal Curley
// This is a file for padding input messages to make it a length that is divisible by 512
// See section 5.1

// input/output header file
#include<stdio.h>
// header file for fixed bit-length integers
#include <stdint.h>

// unions store member variables in same location(i.e if you store a value in one varible, it affects the other )
// declaring union message block
union msgblock{
	// read msg block as 64 element array of bytes (8 bits)
	uint8_t e[64];
	// read msg block as 16 element array of 32-bit-chunks
	uint32_t t[16];
	// read msg block as 8 element array of 64-bit-chunks
	uint64_t s[8];
};

int main(int argc, char *argv[]){
	// getting instance of msgblock
	union msgblock M;
	// variable for number of bytes in message block
	uint64_t nobytes;

	// declaring file pointer
	FILE* f;
	// read first argument on command line as file name
	f = fopen(argv[1], "r");
	// read (1 copy of) 64-byte-chunks and print as long long unsigned-int to console
	while(!feof(f)){
		// fread returns number of bytes in file
	       	nobytes = fread(M.e,1,64,f);
		printf("%llu\n", nobytes);
	}
	// close file
	fclose(f);

	return 0;
}
