#pragma once
#include <stdint.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// string aliases for for string functions
typedef string k64, k48, b56, b28, h64, h48;

// integer aliases (uint64_t) for binary functions
typedef uint64_t ullong, ullong64, ullong56, ullong48, ullong32, ullong28, ullong8;
typedef vector<uint64_t> vector64;

// string functions
void KeyExpansion(k64 key, bool hex);
b56 PermutedChoice1(k64 key);
k48 PermutedChoice2(b56 cd);
b28 Shift(b28 bin, int round);
h48 BinToHex(k48 subkey);

// binary functions
void KeyExpansion(ullong48 subkeys[16], bitset<64> key, bool printHex = false, bool printBin = false);
ullong56 PermutedChoice1(ullong64 key);
ullong48 PermutedChoice2(ullong56 cd);
ullong56 Shift(ullong56 cd, int round);
ullong28 RotateLeft(ullong28 input, int shift);