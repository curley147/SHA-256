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

enum status {READ, PAD0, PAD1, FINISH};

int main(int argc, char *argv[]){
	// getting instance of msgblock
	union msgblock M;
	// variable to count number of bits in file
	uint64_t nobits = 0;
	// variable for number of bytes in message block
	uint64_t nobytes;

	enum status S = READ;

	// declaring file pointer
	FILE* f;
	// read first argument on command line as file name
	f = fopen(argv[1], "r");
	// read (1 copy of) 64-byte-chunks and print as long long unsigned-int to console
	while(S == READ){
		// fread returns number of bytes in file
	       	nobytes = fread(M.e,1,64,f);
		// calculating number of bits from fread output
		nobits = nobits + (nobytes * 8);
		// allowing for 64 bit integer to indicate size of actual message
		if(nobytes < 56){
			printf("found block with less than 56 bytes\n");
			// adding 1 bit and the rest of the byte 0's
			M.e[nobytes] = 0x80;
			// adding 0's to fill up message block to the last 64 bits
			while(nobytes < 56){
				nobytes += 1;
				M.e[nobytes] = 0x00;
			}
			// setting 64 bit integer to indicate size of actual message
			M.s[7] = nobits;
			S = FINISH;
		} else if(nobytes < 64){
			S = PAD0;
			M.e[nobytes] = 0x80;
			while(nobytes < 64){
				nobytes += 1;
				M.e[nobytes] = 0x00;
			}
		} else if(feof(f)){
			S = PAD1;
		}
	}
	// close file
	fclose(f);

	for(int i=0; i<64; i++){
		printf("%x ", M.e[i]);
	//	printf("\n");
	}
	return 0;
}
