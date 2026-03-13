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
		ullong64 tap0 = (shiftReg >> 0 ) & 1; // bit 0 
		ullong64 tap1 = (shiftReg >> 60) & 1; // 1
		ullong64 tap2 = (shiftReg >> 62) & 1; // 2
		ullong64 tap3 = (shiftReg >> 63) & 1; // 3

		ullong64 feedBack = tap0 ^ tap1 ^ tap2 ^ tap3; // XOR taps for feedback

		ullong64 hold = shiftReg & 1;

		shiftReg >>= 1; // shift right to prepare for next step
		shiftReg |= (feedBack << 63); // insert feedback at msb (63)

		IV = (IV << 1) | hold; // add shifted out bit to end of IV
	}
	return IV; // after 64 rounds, IV contains 64 bits
}

