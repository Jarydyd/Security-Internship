#pragma once
#include "KeyExpansion.h"
#include <vector>
using namespace std;

vector8 pkcs7Pad(const vector8& pText, size_t size);
vector8 pkcs7unPad(const vector8 &cText, size_t size);
