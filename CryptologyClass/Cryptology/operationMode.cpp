#include "operationMode.h"
#include "DESEncrypt.h"
#include <bitset>
#include <vector>
#include <cstdint>
#include "padding.h"
#include "KeyExpansion.h"


// ECB
// Ci = EK(Pi)
// CBC
// Ci = EK(Pi xor Ci-1), using DES, xor P1 with the IV then P2 with C1...
// with c0 = IV
// pt will be a vector of 64 bit blocks, as will the PT


void ecbEncrypt(const vector64 &pText, ullong64 key, vector64 &cText)
{
	bitset<64> bitSetKey(key);
	cText.clear();
	cText.reserve(pText.size());

	for (ullong64 ptBlock : pText)
	{
		ullong64 ctBlock = DESEncrypt(ptBlock, bitSetKey, false);
		cText.push_back(ctBlock);
	}
}

void ecbDecrypt(const vector64 &cText, ullong64 key, vector64 &pText)
{
	bitset<64> bitSetKey(key);
	pText.clear();
	pText.reserve(cText.size());

	for (ullong64 ctBlock : cText)
	{
		ullong64 ptBlock = DESEncrypt(ctBlock, bitSetKey, true);
		pText.push_back(ptBlock);
	}
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

static vector64 bytesToBlock(const vector8 &bytes)
{
	vector64 blocks;
	for (size_t i = 0; i < bytes.size(); i += 8)
	{
		ullong64 hold = 0;
		for (int j = 0; j < 8; j++)
		{
			hold = (hold << 8 | bytes[i + j]);
		}
		blocks.push_back(hold);

	}
	return blocks;
}

static vector8 blockToBytes(const vector64 &block)
{
	vector8 bytes;
	for (ullong64 hold : block)
	{
		for (int i = 7; i >= 0; i--)
		{
			ullong8 byte = (hold >> (i * 8)) & 0xFF;
			bytes.push_back(byte);
		}
	}
	return bytes;
}

void padEcbEncrypt(const vector8 &ptBytes, ullong64 key, vector64 &ctBlocks)
{
	
	vector8 padded = pkcs7Pad(ptBytes, 8);
	vector64 blocks = bytesToBlock(padded);
	ecbEncrypt(blocks, key, ctBlocks);
}

void padEcbDecrypt(const vector64& ctBlocks, ullong64 key, vector8 &ptBytes)
{
	vector64 ptBlocks;
	ecbDecrypt(ctBlocks, key, ptBlocks);
	vector8 hold = blockToBytes(ptBlocks);
	ptBytes = pkcs7unPad(hold,8);
}

void padCbcEncrypt(const vector8 &ptBytes, ullong64 key, vector64 &ctBlocks, ullong64 IV)
{
	vector8 padded = pkcs7Pad(ptBytes, 8);
	vector64 blocks = bytesToBlock(padded);
	cbcEncrypt(blocks, key, ctBlocks, IV);
}

void padCbcDecrypt(const vector64 &ctBlocks, ullong64 key, vector8 &ptBytes, ullong64 IV)
{
	vector64 ptBlocks;
	cbcDecrypt(ctBlocks, key, ptBlocks,IV);
	vector8 hold = blockToBytes(ptBlocks);
	ptBytes = pkcs7unPad(hold, 8);
}


