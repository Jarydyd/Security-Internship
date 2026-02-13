#include "CBC.h"
#include "DESEncrypt.h"
#include <bitset>
#include <vector>
#include <cstdint>

// Ci = EK(Pi xor Ci-1), using DES, xor P1 with the IV then P2 with C1...
// with c0 = IV
// pt will be a vector of 64 bit blocks, as will the PT
typedef uint64_t ullong8;


void cbcEncrypt(const vector64 &pText, uint64_t key, vector64 &cText, uint64_t IV)
{
	bitset<64> bitSetKey(key);
	uint64_t prev = IV;

	cText.clear();
	cText.reserve(pText.size());

	for (uint64_t ptBlock : pText)
	{
		uint64_t hold = ptBlock ^ prev; // xor previous ciphertext (IV if first)
		uint64_t ctBlock = DESEncrypt(hold, bitSetKey, false); // encrypt with DES
		cText.push_back(ctBlock); // store ct
		prev = ctBlock; // update
	}
	
}

void cbcDecrypt(const vector64 &cText, uint64_t key, vector64 &pText, uint64_t IV)
{
	bitset<64> bitSetKey(key);
	uint64_t prev = IV;

	pText.clear();
	pText.reserve(cText.size());

	for (uint64_t ctBlock : cText)
	{
		uint64_t hold = DESEncrypt(ctBlock, bitSetKey, true);
		uint64_t ptBlock = hold ^ prev; // xor
		pText.push_back(ptBlock); // push ptb
		prev = ctBlock; // update
	}
}


