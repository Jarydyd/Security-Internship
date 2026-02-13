#pragma once
#include <stdint.h>
#include "DESEncrypt.h"
#include "KeyExpansion.h"
#include <vector>
#include <bitset>
typedef uint64_t ullong, ullong64, ullong56, ullong48, ullong28;
typedef vector<uint64_t> vector64;


using namespace std;

void cbcEncrypt(const vector64 &pText, uint64_t key, vector64 &cText, uint64_t IV);

void cbcDecrypt( );
