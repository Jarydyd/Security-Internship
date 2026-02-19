#include "operationMode.h"
#include "DESEncrypt.h"
#include <bitset>
#include <vector>
#include <cstdint>
#include "KeyExpansion.h"


// ECB
// Ci = EK(Pi)
// CBC
// Ci = EK(Pi xor Ci-1), using DES, xor P1 with the IV then P2 with C1...
// with c0 = IV
// pt will be a vector of 64 bit blocks, as will the PT


void ecbEncrypt(const vector64 &pText, ullong64 key, vector64 &cText)
{
	vector64 hold;
	
}

void ecbDecrypt(const vector64 &cText, ullong64 key, vector64 &pText)
{
}

void cbcEncrypt(const vector64 &pText, ullong64 key, vector64 &cText, ullong64 IV)
{
	bitset<64> bitSetKey(key);
	ullong64 prev = IV;

	cText.clear();
	cText.reserve(pText.size());

	for (ullong64 ptBlock : pText)
	{
		ullong64 hold = ptBlock ^ prev; // xor previous ciphertext (IV if first)
		ullong64 ctBlock = DESEncrypt(hold, bitSetKey, false); // encrypt with DES
		cText.push_back(ctBlock); // store ct
		prev = ctBlock; // update
	}
	
}

void cbcDecrypt(const vector64 &cText, ullong64 key, vector64 &pText, ullong64 IV)
{
	bitset<64> bitSetKey(key);
	ullong64 prev = IV;

	pText.clear();
	pText.reserve(cText.size());

	for (ullong64 ctBlock : cText)
	{
		ullong64 hold = DESEncrypt(ctBlock, bitSetKey, true);
		ullong64 ptBlock = hold ^ prev; // xor
		pText.push_back(ptBlock); // push ptb
		prev = ctBlock; // update
	}
}


