#include "CBC.h"
#include "DESEncrypt.h"
#include "bitset"
#include "vector"
// Ci = EK(Pi xor Ci-1), using DES, xor P1 with the IV then P2 with C1...
// with c0 = IV
// pt will be a vector of 64 bit blocks, as will the PT
typedef uint64_t ullong8;


void cbcEncrypt(const vector64 &pText, uint64_t key, vector64 &cText, uint64_t IV)
{
	bitset<64> bitSetKey(key);
	uint64_t prevIV = IV;

	cText.clear();
	cText.reserve(pText.size());

	for (uint64_t current : pText)
	{
		uint64_t hold = current ^ IV; // xor previous ciphertext (IV if first)
		uint64_t cBlock = DESEncrypt(hold, bitSetKey, false); // encrypt with DES
		cText.push_back(cBlock); // store ct
		prevIV = cBlock; // update

	}

	return;
	
}

void cbcDecrypt()
{
}


