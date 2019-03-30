// Micheal Curley
// Secure Hash Algorithm (256-bit)
// https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=919060

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
// A flag for where we are in reading the file
enum status {READ, PAD0, PAD1, FINISH};

// See section 4.1.2 for definitions
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);
uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

// See section 3.2 for definitions
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);
// Retrieves the next message block
int nextmsgblock(FILE *file, union msgblock *M, enum status *S, uint64_t *nobits);

// calculates the SHA-256 of a file
void sha256(FILE *file);



int main(int argc, char *argv[]){

	// declaring file pointer	
	FILE* file;
	// read first argument on command line as file name
	file = fopen(argv[1], "r");
	// run secure hash algorithm on the file
	sha256(file);

	// close file
	fclose(file);
	
	return 0;

}

void sha256(FILE *file){
	// getting instance of msgblock
	union msgblock M;
	// variable to count number of bits in file
	uint64_t nobits = 0;
	// set flag to read
	enum status S = READ;

	// The K constants, see section 4.2.2 for definitions
	uint32_t K[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
	// message schedule (Section 6.2)
	uint32_t W[64];
	// working variables (section 6.2)
	uint32_t a, b, c, d, e, f, g, h;
	// two temporary variables (Section 6.2)
	uint32_t T1, T2;

	// hash digest (256 bit output)
	// initial values from Section 5.3.3
	uint32_t H[8] = {
		  0x6a09e667
		, 0xbb67ae85	
		, 0x3c6ef372
		, 0xa54ff53a
		, 0x510e527f
		, 0x9b05688c
		, 0x1f83d9ab
		, 0x5be0cd19	
	};

	// for looping
	int i, t;
	
	// Loop through the message blocks as per page 22
	while(nextmsgblock(file, &M, &S, &nobits)){
		// from page 22. W[t] = M[t] for 0<=t<=15
		for(t=0; t<16;	t++)
			W[t]=M.t[t];
		// from page 22. W[t] = ...
		for(t=16; t<64; t++)
			W[t] = sig1(W[t-2])+W[t-7]+sig0(W[t-15])+W[t-16];

		// Initialise a,b,c,d,e,f,g,h as per step 2, page 22
		a=H[0]; b=H[1]; c=H[2]; d=H[3]; e=H[4]; f=H[5]; g=H[6]; h=H[7];
	
		// Step 3
		for(t=0; t<64; t++){
			T1 = h + SIG1(e) + Ch(e,f,g) + K[t] + W[t];
			T2 = SIG0(a) + Maj(a,b,c);
			h=g;
			g=f;
			f=e;
			e=d+T1;
			d=c;
			c=b;
			b=a;
			a=T1+T2;
		}

		// Step 4
		H[0] = a+H[0];
		H[1] = b+H[1];
		H[2] = c+H[2];
		H[3] = d+H[3];
		H[4] = e+H[4];
		H[5] = f+H[5];
		H[6] = g+H[6];
		H[7] = h+H[7];
	}	
	printf("%08x %08x %08x %08x %08x %08x %08x %08x \n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
}
//Add (static) inline to one-liner functions to reduce overhead
// e.g static inline uint32_T rotr(uint32_t n, uint32_t x){

// See section 3.2 for definitions
uint32_t rotr(uint32_t n, uint32_t x){
	return (x >> n) | (x << (32-n));
}
uint32_t shr(uint32_t n, uint32_t x){
	return (x >> n);
}

uint32_t sig0(uint32_t x){
	// See Sections 3.2 and 4.1.2 for definitions
	return (rotr(7, x) ^ rotr(18, x) ^ shr(3, x));
}
uint32_t sig1(uint32_t x){
	// See Sections 3.2 and 4.1.2 for definitions
	return (rotr(17, x) ^ rotr(19, x) ^ shr(10, x));

}
// See section 4.1.2 for definitions
uint32_t SIG0(uint32_t x){
	return (rotr(2,x) ^ rotr(13,x) ^ rotr(22,x));
}
uint32_t SIG1(uint32_t x){
	return (rotr(6,x) ^ rotr(11,x) ^ rotr(25,x));
}
// See section 4.1.2 for definitions
// Ch (Choose) is a function that wherever the bits in x are 1 it picks out the corresponding bits in y
// and wherever the bits in x are 0 it picks out the corresponding bits in z and then does an XOR on it
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return ((x & y) ^ ((!x) & z));
}
// Maj (Majority) is a function that wherever the majority value from bits x,y,z is 1, the output is 1 and 
// wherever the the majority value from bits x,y,z is 0, the output is 0.
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
	return ((x & y) ^ (x & z) ^ (y & z));
}
// function to return next message block
int nextmsgblock(FILE *file, union msgblock *M, enum status *S, uint64_t *nobits){
	// variable for number of bytes in message block
	uint64_t nobytes;

	// For looping
	int i;

	// if we've finished all the msg blocks, S should be FINISH
	if(*S == FINISH){
		return 0;
	}
	// otherwise check if we need another block for padding
	if(*S == PAD0 || *S == PAD1){
		for(i=0;i<56;i++){
			M->e[i] = 0x00;
		}
		// sets last 64 bits to integer indicating number of bits in actual message (big-endian)
		M->s[7] = *nobits;
		// Tell S we're finished
		*S = FINISH;
		// set first bit of M to 1
		if(*S == PAD1){
			M->e[0] = 0x80;
			// keep loop going in sha256 for one more iteration
			return 1;
		}

	}
	// if we get down here we haven't finished reading the file (S == READ)
		
	// fread returns number of bytes in file
       	nobytes = fread(M->e,1,64,file);
	// calculating number of bits from fread output
	*nobits = *nobits + (nobytes * 8);
	// allowing for 64 bit integer to indicate size of actual message
	if(nobytes < 56){
		// adding 1 bit and the rest of the byte 0's
		M->e[nobytes] = 0x80;
		// adding 0's to fill up message block to the last 64 bits
		while(nobytes < 56){
			nobytes += 1;
			M->e[nobytes] = 0x00;
		}
		// setting 64 bit integer to indicate size of actual message
		M->s[7] = *nobits;
		// set flag to finish
		*S = FINISH;
	} else if(nobytes < 64){ // not enough room in rest of block to pad
		// set flag to PAD0
		*S = PAD0;
		// adding 1 bit and the rest of the byte 0's
		M->e[nobytes] = 0x80;
		// adding 0's to fill up message block to the last 64 bits
		while(nobytes < 64){
			nobytes += 1;
			M->e[nobytes] = 0x00;
		}
	} else if(feof(file)){ // exactly 512 or multiple of 512 bits
		// set flag to PAD1
		*S = PAD1;
	}

	// return 1 so this function is called again
	return 1;
}

