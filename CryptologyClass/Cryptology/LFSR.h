#pragma once
#include <stdint.h>
#include "keyExpansion.h" // typedefs
using namespace std;

void isSeeded();

ullong64 lfsrIV(ullong64 seed);
