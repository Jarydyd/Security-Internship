# Security-Internship
CPSC 487 Internship (Spring 2026)
Proposed Semester Project: Full DES Implementation and Security Analysis
The objective of this project is to implement the full DES encryption and decryption algorithms, analyze the role of its core components, and explore its security limitations.
Phase 1: Completing the DES Core (Weeks 1-4) 
The student has already completed the Key Schedule (generating the 16 subkeys K1 through K16). This phase focuses on the data path for a single 64-bit plaintext block.
•	1. Initial Permutation (IP): Implement the IP on the 64-bit plaintext block.
•	2. The 16 Rounds of Feistel Cipher:
Implement the round function f (Ri-1, Ki) = P (S(E(Ri-1 )  Ki)).
	Expansion Permutation (E): Implement the E box, expanding the 32-bit Ri-1 to 48 bits.
	S-Box Implementation (S): Implement all eight S-Boxes—the non-linear substitution tables. This is arguably the most critical and complex part of the round function.
	Permutation Box (P): Implement the final permutation on the 32-bit output of the S-Boxes.
Combine these steps correctly with the XOR and the Swapping of the left (L) and right (R) halves to complete a full round: Li = Ri-1 and Ri   = Li-1   f (Ri-1 , Ki).
•	3. Final Permutation (IP-1): Implement the inverse of the initial permutation on the final 64-bit block (R16, L16).
•	4. Decryption Implementation: Show that the same code can be used for decryption simply by applying the subkeys in reverse order K16, K15, …, K1).
 
Phase 2: Block Modes and File Encryption (Weeks 5-8) 
DES is a block cipher, which means it only encrypts 64 bits at a time. This phase extends the implementation to handle data of arbitrary length (e.g., a text file) using a Block Cipher Mode of Operation.
•	1. Electronic Codebook (ECB) Mode: Implement ECB mode.
o	Encrypt a sample text file or image in ECB mode.
o	Analysis: Explain the security weakness of ECB mode (the same plaintext block always produces the same ciphertext block). Provide an example visualization of this using a simple image.
•	2. Cipher Block Chaining (CBC) Mode: Implement CBC mode.
o	Requires an Initialization Vector (IV). Implement a way to generate a random 64-bit IV and prepend it to the ciphertext.
o	Encrypt and decrypt the same sample file using CBC mode.
o	Analysis: Explain how CBC mode mitigates the weaknesses of ECB mode (by introducing dependency on the previous block's ciphertext and the IV).
•	3. Padding: Implement a standard padding scheme (e.g., PKCS#5 or PKCS#7) to handle plaintext that is not a multiple of the 64-bit block size.
 
Phase 3: Analysis and Presentation (Weeks 9-12) 
The final phase involves a critical analysis of the implemented cipher and its real-world context.
•	1. Presentation/Report: Create a comprehensive report and presentation covering:
o	A detailed explanation of the Feistel structure and why it's used.
o	The role of diffusion (achieved by $P$ and key shifts) and confusion (achieved by the S-Boxes) in DES.
o	The complete security analysis of DES: Why is a 56-bit key no longer secure? Discuss the concept of a brute-force attack and the computational resources required today (e.g., DES cracker machines like Deep Crack).
•	2. Key Generation Upgrade (Triple DES/3DES):
o	Implement the Triple DES (3DES) algorithm using E-D-E (Encrypt-Decrypt-Encrypt) with two or three independent keys (K1, K2, K3).
o	Demonstrate 3DES encryption and decryption.
o	Analysis: Discuss why 3DES, despite having a larger effective key size (112 or 168 bits), is being phased out in favor of modern ciphers like AES (e.g., its 64-bit block size being too small).
