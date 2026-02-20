#include "DESEncrypt.h"
#include "KeyExpansion.h"
#include "DESTables.h" // contains tables: P E IP FP SBOXES and permutation for f function
#include <bitset>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace DESTables;

ullong64 DESEncrypt(ullong64 block, bitset<64> key, bool decrypt) 
{
	cout << endl << "0x" << hex << uppercase << setw(16) << setfill('0') 
		 << key.to_ullong() << dec << setfill(' ') << endl; // set to hex, print block, reset to dec
	block = Scramble(block); // apply ip to block
	ullong32 left = block >> 32; // split block into left and right halves
	ullong32 right = block & 0xFFFFFFFF;
	ullong48 subkeys[16] = {}; // also holds eah subkey
	KeyExpansion(subkeys, key, false, false); // generates subkeys
	for (int round = 0; round < 16; round++) 
	{
		int hold = decrypt ? (15 - round) : round; // if decrypt, reverse order of subkeys, else don't
		ullong48 subkey = subkeys[hold]; // current subkey
		ullong32 newleft = right; // feistel
		ullong32 newright = left ^ f_function(right, subkey); // xor left with right key permuted through f function
		left = newleft; // update for next round
		right = newright; // update for next round
	}
	ullong64 outblock = (right << 32) | left; // concat halves together, note that CT = right left
	outblock = Unscramble(outblock); // apply fp to block
	cout << outblock << endl;
	return outblock;
}

// just des empansion function
ullong48 expand(ullong32 half) 
{
	bitset<32> input(half); 
	bitset<48> output;
	for (int i = 0; i < size(E); i++) // expansion table; ie map 32 bits to 48 bits
		output[47 - i] = input[32 - E[i]];
	return output.to_ullong();
}

// des f function
ullong32 f_function(ullong32 half, ullong48 subkey) 
{
	ullong48 unsubbed = expand(half) ^ subkey; // expand then xor with subkey
	ullong32 subbed = Substitution(unsubbed); 
	ullong32 permuted = Permutation(subbed);
	return permuted;
}

// apply initial permutation
ullong64 Scramble(ullong64 block) 
{
	bitset<64> input(block);
	bitset<64> output;
	for (int i = 0; i < size(IP); i++)
		output[63 - i] = input[64 - IP[i]];
	return output.to_ullong();
}

// final permutation
ullong64 Unscramble(ullong64 block) 
{
	bitset<64> input(block);
	bitset<64> output;
	for (int i = 0; i < size(FP); i++)
		output[63 - i] = input[64 - FP[i]];
	return output.to_ullong();
}

ullong32 Substitution(ullong48 input) 
{
	ullong32 output = 0; // hold
	for (int i = 0; i < 8; i++)  // for each sbox
	{
		int shift = 48 - 6 * (i + 1);
		bitset<6>inbox((input >> shift) & 0x3F);
		// note: bitsets are indexed from the right 
		int row = inbox[5] << 1 | inbox[0]; // outer two bits = row, 
		int col = inbox[4] << 3 | inbox[3] << 2 | inbox[2] << 1 | inbox[1]; // inner four bits = col
		
		int outshift = 32 - 4 * (i + 1); 
		output |= SBoxes[i][row][col] << outshift; // find sbox, OR it with output at correct position
	}
	return output;
}

ullong32 Permutation(ullong32 half) 
{
	bitset<32> input(half);
	bitset<32> output;
	for (int i = 0; i < size(P); i++)
		output[31 - i] = input[32 - P[i]];
	return output.to_ullong();
}

static void printHex64(ullong64 v)
{
	cout << "0x" << hex << uppercase << setw(16) << setfill('0') << v << dec << setfill(' ');
}
