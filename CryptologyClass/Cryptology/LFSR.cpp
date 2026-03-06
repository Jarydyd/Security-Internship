#include "LFSR.h"
#include <stdlib.h> // random
using namespace std;




ullong64 lfsrIV(ullong64 seed)
{
	ullong64 shiftReg = seed;
	ullong64 IV = 0;
	for (int i = 0; i < 64; i++)
	{
		// may want to set taps to 0,60,62,63
		ullong64 tap0 = shiftReg & 1; // 0 
		ullong64 tap1 = (shiftReg >> 1) & 1; // 1
		ullong64 tap2 = (shiftReg >> 2) & 1; // 2
		ullong64 tap3 = (shiftReg >> 3) & 1; // 3

		ullong64 feedBack = tap0 ^ tap1 ^ tap2 ^ tap3; // XOR taps for feedback

		shiftReg >>= 1; // shift right
		shiftReg |= (feedBack << 63); // insert feedback at msb

		IV = IV << 1 | tap0; // shift IV left and concat 
	}
	return IV; // after 64 rounds, IV contains 64 bits
}

