#include "LFSR.h"
#include <stdlib.h> // random
using namespace std;


ullong64 lfsrIV(ullong64 seed)
{
	ullong64 shiftReg = seed;
	ullong64 IV = 0;
	for (int i = 0; i < 64; i++)
	{
		
		// set taps to 63, 62, 60, 59 for max period of 2^64 - 1
		ullong64 tap0 = (shiftReg >> 63) & 1; // MSB
		ullong64 tap1 = (shiftReg >> 62) & 1; // 
		ullong64 tap2 = (shiftReg >> 60) & 1; // 
		ullong64 tap3 = (shiftReg >> 59) & 1; // 

		ullong64 feedBack = tap0 ^ tap1 ^ tap2 ^ tap3; // XOR taps for feedback


		shiftReg <<= 1; // shift left to prepare for next step
		shiftReg |= (feedBack); // insert feedback at LSB

		IV = (IV << 1) | tap0; // add shifted out bit to end of IV

	}
	return IV; // after 64 rounds, IV contains 64 bits
}

