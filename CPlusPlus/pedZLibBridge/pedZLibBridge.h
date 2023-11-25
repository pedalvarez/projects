#ifndef _PEDZLIBBRIDGEAPI_H_
#define _PEDZLIBBRIDGEAPI_H_

#ifndef PEDZLIBBRIDGEAPI
  #define PEDZLIBBRIDGEAPI 
#endif

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

	PEDZLIBBRIDGEAPI char* Compress(BYTE* blob, size_t blobLen, size_t bufferSize, BYTE* compressionDict, size_t dicLen, int* resultLen);

	PEDZLIBBRIDGEAPI char* Decompress(BYTE* blob, size_t blobLen, size_t bufferSize, BYTE* compressionDict, size_t dicLen, int* resultLen);

#ifdef __cplusplus
}
#endif

#endif