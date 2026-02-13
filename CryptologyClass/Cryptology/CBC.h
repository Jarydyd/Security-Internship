#pragma once
#include <stdint.h>
#include "DESEncrypt.h"
#include "KeyExpansion.h"
#include <vector>
#include <bitset>
typedef uint64_t ullong, ullong64, ullong56, ullong48, ullong28;
typedef vector<uint64_t> vector64;


using namespace std;

void cbcEncrypt(const vector64 &pText, ullong64 key, vector64 &cText, ullong64 IV);

void cbcDecrypt(const vector64 &cText, ullong64 key, vector64 &pText, ullong64 IV);
