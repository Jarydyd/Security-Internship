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

// these four functions operate on 64 bit (8 byte) blocks
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

// converts bytes to 64 bit blocks as name implies, msb first; i.e. index 0 becomes MSB of first block
// pt --> pkcspad --> bytesToBlock --> CT
// CT --> block to byte --> pkcsunpad --> PT
static vector64 bytesToBlock(const vector8 &bytes)
{
	vector64 blocks;
	for (size_t i = 0; i < bytes.size(); i += 8) // 8 bytes/block
	{
		ullong64 hold = 0;
		for (int j = 0; j < 8; j++)
		{
			hold = (hold << 8 | bytes[i + j]); // shift previous then concat byte
		}
		blocks.push_back(hold); // append blocks

	}
	return blocks;
}

// ... converts 64 bit block to bytes (MSB)
static vector8 blockToBytes(const vector64 &block)
{
	vector8 bytes;
	for (ullong64 hold : block) // for each block
	{
		for (int i = 7; i >= 0; i--) // starting from MSB...
		{
			ullong8 byte = (hold >> (i * 8)) & 0xFF; // extract byte
			bytes.push_back(byte); // concat byte
		}
	}
	return bytes;
}

// padded versions that handle arbitrary inputs by implementing PKCS#7
void padEcbEncrypt(const vector8 &ptBytes, ullong64 key, vector64 &ctBlocks)
{
	
	vector8 padded = pkcs7Pad(ptBytes, 8); // pad to 8 byte blocks (DES) 
	vector64 blocks = bytesToBlock(padded); // put bytes in block (MSB)
	ecbEncrypt(blocks, key, ctBlocks);
} 

void padEcbDecrypt(const vector64 &ctBlocks, ullong64 key, vector8 &ptBytes)
{
	vector64 ptBlocks;
	ecbDecrypt(ctBlocks, key, ptBlocks); 
	vector8 hold = blockToBytes(ptBlocks); // unpack blocks into bytes 
	ptBytes = pkcs7unPad(hold,8); // remove padding, noting that block size is 8
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


