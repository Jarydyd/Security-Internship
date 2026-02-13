// Jaryd Rockman
// git test git final test, please work :)
// Dr. Eun-Joo Lee 
// Purpose: 1. Key Schedule Implementation: 
// Program the DES Key Schedule, taking a 64-bit key (including parity bits) and correctly performing:
// Parity Drop/Initial Permutation (PC-1) to get the 56-bit key.
// Splitting into C_0 and D_0 28-bit halves.
// Left Circular Shifts for each of the 16 rounds.
// Compression Permutation (PC-2) to generate the 48-bit subkey K_i for each round i=1 to 16. 
// 2. 
// Output: Print all 16 subkeys in binary and hexadecimal format. 

#include "KeyExpansion.h" // contains key expansion/shceulde functions
#include "DESEncrypt.h" // contains functions necessary for DES encryption
#include "CBC.h" // contains functions necessary for CBC mode
#include "LFSR.h" // contains functions necessary for LFSR IV generation
#include <iostream>
#include <bitset>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;
typedef vector<uint64_t> vector64;

ullong64 paritybits = 0x0101010101010101ULL; // mask of parity bits

// creates subkeys based off provided testkey, then performs a small bruteforce attack, skipping keys with respect to set parity bits
int main() {
	vector64 pT, cT;
	ullong64 key, IV;
	IV = 0xFFFFFFFFFFFFFFFFULL; // sample IV, needs to be changed to be deterministic
	ullong testPT = 0x0123456789ABCDEFULL; // sample test plaintext
	ullong testkey = 0x0123456789ABCDEFULL; // sample test key
	pT.push_back(testPT);

	cbcEncrypt(pT, testkey, cT, IV);
	for (uint64_t current : cT)
	{
		cout << "0x" << hex << uppercase << current << dec << endl;
	}

	// small brute force attack demonstration
	// ullong subkeys[16]; // holds each subkey

	/*ullong64 secretkey = 1ULL << 20; // sample secretkey, deliberiately small for shorter tests, can be any 64 bit value

	// if secretkey includes parity bits, increment them.
	while (secretkey & paritybits) secretkey += secretkey & paritybits;
	cout << "Secret key = 0x" << hex << uppercase << setw(16) << right << setfill('0') << secretkey << endl;

	ullong64 plaintext = 0; // sample plaintext, chosen to be 0 for simplicity
	ullong64 ciphertext = DESEncrypt(plaintext, bitset<64>(secretkey)); // encrypt PT with sample secret key
	ullong64 foundkey = 0;
	ullong64 searchcount = 0;
	auto start = chrono::high_resolution_clock::now(); // see how long search takes
	while (true) 
	{
		// skip keys with parity bits set to reduce search space
		while(foundkey & paritybits) foundkey += foundkey & paritybits;
		ullong64 encryptedtext = DESEncrypt(plaintext, bitset<64>(foundkey)); // test current key
		searchcount++; // increments per key, used to display total keys checked
		if (encryptedtext == ciphertext) break; // if found key, break
		foundkey++;
	}
	auto end = chrono::high_resolution_clock::now(); 

	cout << "Found Key: 0x" << hex << uppercase << setw(16) << right << setfill('0') << foundkey << endl;
	cout << "Time spent: " << chrono::duration<double>(end - start).count() << " seconds." << endl;
	cout << "Keys checked: " << dec << searchcount << endl;*/
	string close;
	cin >> close;
	return 0;
}


// alternative code that that can be used to allow user input as a key
/*
	string keyString = "";
	cout << "Enter Key? [y/n] ";
	char answer;
	cin >> answer;
	if (toupper(answer) != 'Y')
		keyString = "0000000100100011010001010110011110001001101010111100110111101111";
	else
	{
		cout << "Enter a 64 bit key in binary: ";
		cin >> keyString;
	}
	//KeyExpansion(keyString, false);
	cout << endl;
	KeyExpansion(keyString, true);

	bitset<64> keybits(keyString);

	uint64_t subkeys[16] = {};
	//KeyExpansion(subkeys, keybits, false);
	cout << endl;
	KeyExpansion(subkeys, keybits, true);

	*/

