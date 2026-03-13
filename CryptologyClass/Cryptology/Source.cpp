// Jaryd Rockman
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
#include "operationMode.h" // contains functions necessary for CBC mode
#include "LFSR.h" // contains functions necessary for LFSR IV generation
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cstdint>
using namespace std;

int main() {

	vector8 pTbytes;
	string pT = "Hello Dr. Lee";
	string superLongPT = "This is a super duper long test pt that im just checking out, this will be needlessly long for no reason other then because i want to type for a little bit right now as a little break and we will see if my code works with this type of length";
	string shortPT = "s";
	string testPT = "0123456789ABCDEF"; // sample test plaintext
	ullong64 testKey = 0x0123456789ABCDEFULL; // sample test key

	ullong64 IV = lfsrIV(testKey); // just see with testkey


	ullong IV2 = 0xFFFFFFFFFFFFFFFFULL;
	for (char c : pT)
	{
		pTbytes.push_back(static_cast<ullong8>(c));
	}
	

	vector64 ecbEncrypt;
	padEcbEncrypt(pTbytes, testKey, ecbEncrypt);
	cout << "ECB ciphertext: " << endl;
	for (auto c : ecbEncrypt)
	{
		cout << hex << uppercase << c;
	}
	cout << "\n------------------------------------------\n";

	vector8 ecbDecrypt;
	padEcbDecrypt(ecbEncrypt, testKey, ecbDecrypt);
	cout << "ECB plaintext: " << endl;
	for (char c : ecbDecrypt)
	{
		cout << c;
	}
	cout << "\n------------------------------------------\n";

	vector64 cbcEncrypt;
	padCbcEncrypt(pTbytes, testKey, cbcEncrypt, IV);
	cout << "CBC ciphertext: " << endl;
	for (auto c : cbcEncrypt)
	{
		cout << hex << uppercase << c;
	}
	cout << "\n------------------------------------------\n";

	vector8 cbcDecrypt;
	padCbcDecrypt(cbcEncrypt, testKey, cbcDecrypt, IV);
	cout << "CBC plaintext:" << endl;
	for (char c : cbcDecrypt)
	{
		cout << c;
	}



	string close;
	cin >> close;
	return 0;
}



int case2()
{
	// creates subkeys based off provided testkey, then performs a small bruteforce attack, skipping keys with respect to set parity bits
	// alternative code that that can be used to allow user input as a key
	ullong subkeys[16]; // holds each subkey
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

	//KeyExpansion(subkeys, keybits, false);
	cout << endl;
	KeyExpansion(subkeys, keybits, true);
	return 0;
}


int bruteForce()
{

	/*/small brute force attack demonstration
	not updated to support current function parameters
		ullong64 paritybits = 0x0101010101010101ULL; // mask of parity bits

		ullong64 secretkey = 1ULL << 20; // sample secretkey, deliberiately small for shorter tests, can be any 64 bit value

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
		return 0;
}

int unpaddedModes()
{
	vector64 pT, pT2, cT;
	ullong64 IV = 0xFFFFFFFFFFFFFFFFULL; // sample IV, needs to be changed to be deterministic
	ullong testPT = 0x0123456789ABCDEFULL; // sample test plaintext
	ullong testPT2 = 0xFEDCBA9876543210ULL; // sample test key 2

	ullong testkey = 0x0123456789ABCDEFULL; // sample test key
	pT.clear(); // ensure clear
	pT.push_back(testPT); // load vector
	pT.push_back(testPT2);


	ecbEncrypt(pT, testkey, cT);
	for (size_t i = 0; i < cT.size(); ++i)
	{
		cout << "ECB CT = 0x" << hex << uppercase << cT[i] << dec << endl;
	}

	pT2.clear();
	ecbDecrypt(cT, testkey, pT2);
	for (size_t i = 0; i < pT2.size(); ++i)
	{
		cout << "ECB Recovered plaintext is 0x" << hex << uppercase << pT2[i] << dec << endl;
	}
	cT.clear();

	cbcEncrypt(pT, testkey, cT, IV);
	for (size_t i = 0; i < cT.size(); ++i)
	{
		cout << "CBC CT = 0x" << hex << uppercase << cT[i] << dec << endl;
	}


	pT2.clear();
	cbcDecrypt(cT, testkey, pT2, IV);

	for (size_t i = 0; i < pT2.size(); ++i)
	{
		cout << "CBC Recovered plaintext is 0x" << hex << uppercase << pT2[i] << dec << endl;
	}
	return 0;
}
	
