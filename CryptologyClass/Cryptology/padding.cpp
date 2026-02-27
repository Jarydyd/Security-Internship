#include "padding.h"

vector8 pkcs7Pad(const vector8 &pText, size_t size)
{
	vector8 hold = pText;
    size_t padSize = (size - (pText.size() % size)); //make number of padding bytes = multiple of block size
    if (padSize == 0) // if padSize is 0 then a full block of padding is needed
    {
        padSize = size;
    }
    
    ullong8 padByte = static_cast<ullong8>(padSize); // store padsize
	hold.insert(hold.end(), padSize, padByte); // insert pad bytes
    return hold;
}

vector8 pkcs7unPad(const vector8 &cText, size_t size)
{
    if (cText.empty()) // if empty, invalid
    {
        return cText; 
    }

    ullong8 back = cText.back(); // read back for pad indicator (store value)
    size_t padSize = static_cast<size_t>(back);
    if (padSize == 0 || padSize > cText.size() || padSize > size) // invalid if padsize !>0
    {
        return cText;
    }

    // validate the pad value at each padding byte
    for (size_t i = 0; i < padSize; ++i)
    {
        // compare each end byte to pad indicator
        if (cText[cText.size() - 1 - i] != back) 
        {
            return cText; // if it doesnt match, invalid, return cipher text
        }
    }

    // if got through all checks that pkcs#7 calls for, then return vector without the padding indicators.
    return vector8(cText.begin(), cText.end() - padSize);

}
