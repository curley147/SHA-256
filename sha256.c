// Micheal Curley
// Secure Hash Algorithm (256-bit)
// https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=919060

// input/output header file
#include<stdio>
// header file for fixed bit-length integers
#include <stdint>

sha256();

int main(int argc. char *argv[]){

	sha256();

	return 0;

}

sha256(){
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
		0xbb67ae85	
		0x3c6ef372
		0xa54ff53a
		510e527f
		0x9b05688c
		0x1f83d9ab
		0x5be0cd19	
	};
}

