#include "padding.h"

vector8 pkcs7Pad(const vector8 &pText, size_t size)
{
	vector8 hold = pText;
    size_t padSize = (size - (pText.size() % size));
    if (padSize == 0)
    {
        padSize = size;
    }
    ullong8 padByte = static_cast<ullong8>(padSize);
	hold.insert(hold.end(), padSize, padByte);
    return hold;
}

vector8 pkcs7unPad(const vector8 &cText, size_t size)
{
    if (cText.empty()) // if empty, invalid
    {
        return cText; 
    }

    ullong8 back = cText.back();
    size_t padSize = static_cast<size_t>(back);
    if (padSize == 0 || padSize > cText.size() || padSize > size) // if padSize = 0 or is greater then size or ctext size, invalid
    {
        return cText;
    }
    for (size_t i = 0; i < padSize; ++i)
    {
        if (cText[cText.size() - 1 - i] != back) 
        {
            return cText; 
        }
    }
    return vector8(cText.begin(), cText.end() - padSize);

}
