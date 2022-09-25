#include <stdio.h>
#include <combaseapi.h>
#include "pedZLibBridge.h"
#include "pedZLib.h"

#ifndef NDEBUG
std::string string_to_hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}
#endif

PEDZLIBBRIDGEAPI char* Compress(BYTE* data, size_t dataLen, size_t bufferSize, const char* compressionDict, int* resultLen) {
    
    std::string in(reinterpret_cast<const char*>(data),dataLen);

#ifndef NDEBUG
    printf("Compress, before: %s\n", in.c_str());
#endif

	std::string s  = Compress(in.c_str(), dataLen, bufferSize, compressionDict);
     ULONG ulSize = (ULONG)s.size();
    *resultLen = ulSize;

#ifndef NDEBUG
    printf("Compress, compressed HEX: %s\n", string_to_hex(s).c_str());
    printf("Compress, compressed size %d\n", ulSize);
#endif

    const char* szSampleString = s.c_str();    
    char* pszReturn = NULL;
    pszReturn = (char*)::CoTaskMemAlloc(ulSize);
    memcpy_s(const_cast<char*>(pszReturn), ulSize, szSampleString, ulSize);    
    return pszReturn;
 }

PEDZLIBBRIDGEAPI char* Decompress(BYTE* data, size_t dataLen, size_t bufferSize, const char* compressionDict, int* resultLen) {

    std::string in(reinterpret_cast<const char*>(data), dataLen);

#ifndef NDEBUG
    printf("Decompress, compressed HEX: %s\n", string_to_hex(in).c_str());
    printf("Compress, compressed size %d\n", dataLen);
#endif

    std::string s = Decompress(in.c_str(), dataLen, bufferSize, compressionDict);
    ULONG ulSize = (ULONG)s.size();
    *resultLen = ulSize;

#ifndef NDEBUG
    printf("Decompress, decompressed HEX: %s\n", string_to_hex(s).c_str());
    printf("Decompress, decompressed size %d\n", ulSize);
#endif

    const char* szSampleString = s.c_str();
    char* pszReturn = NULL;
    pszReturn = (char*)::CoTaskMemAlloc(ulSize);
    memcpy_s(const_cast<char*>(pszReturn), ulSize, szSampleString, ulSize);
    return pszReturn;
}