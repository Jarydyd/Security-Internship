#pragma once
#include <stdint.h>
#include "DESEncrypt.h"
#include "KeyExpansion.h"
#include <vector>
#include <bitset>



using namespace std;

void ecbEncrypt(const vector64 &pText, ullong64 key, vector64 &cText);
void ecbDecrypt(const vector64 &cText, ullong64 key, vector64 &pText);

void cbcEncrypt(const vector64 &pText, ullong64 key, vector64 &cText, ullong64 IV);
void cbcDecrypt(const vector64 &cText, ullong64 key, vector64 &pText, ullong64 IV);

static vector64 bytesToBlock(const vector8 &bytes);
static vector8 blockToBytes(const vector64 &block);

// for pkcs#7 padding, plaintext is padded to multiple of 64 bits
void padEcbEncrypt(const vector8 &padPText, ullong64 key, vector64 &padCText);
void padEcbDecrypt(const vector64 &padCText, ullong64 key, vector8 &padPText);

void padCbcEncrypt(const vector8 &padPText, ullong64 key, vector64 &padCText, ullong64 IV);
void padCbcDecrypt(const vector64 &padCText, ullong64 key, vector8 &padPText, ullong64 IV);

