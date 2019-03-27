// Micheal Curley
// Secure Hash Algorithm (256-bit)
// https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=919060

// input/output header file
#include<stdio>
// header file for fixed bit-length integers
#include <stdint>

void sha256();

// See section 4.1.2 for definitions
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// See section 3.2 for definitions
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

int main(int argc. char *argv[]){

	sha256();

	return 0;

}

void sha256(){
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
		, 510e527f
		, 0x9b05688c
		, 0x1f83d9ab
		, 0x5be0cd19	
	};

	// the current message block
	uint32_t M[16];

	// for looping
	int t;

	// from page 22. W[t] = M[t] for 0<=t<=15
	for(t=0, t<16, t++)
		W[t]=M[t];
	//from page 22. W[t] = ...
	for(t=16, t<64, t++)
		sig_1(W[t-2])+W[t-7]+sig_0(W[t-15])+W[t-16];


}

uint32_t sig0(uint32_t x){
	//See Sections 3.2 and 4.1.2 for definitions
	//ROTR_n(x) = (x >> n)|(x << (32-n))
	//SHR_n(x) = (x >> n)

}
uint32_t sig1(uint32_t x){

}

