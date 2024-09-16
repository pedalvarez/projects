#pragma once
#include <string>
#include <span>

constexpr ULONG CHUNK_SIZE = 4096;

#define SYMM_KEY_SIZE_SECRET 16

//Set IV
static const BYTE rgbIV[] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

//Set AES KEY
static const BYTE Aes128Password[] =
{
	'P', 'e', 'd', 'r', 'i', 't', 'o', '#', 
	'i', 's', '#', 't', 'h', 'e', 's', 't'
};

class CNGCryptFile  
{	
	//Handle 
	BCRYPT_ALG_HANDLE       m_hAesAlg		;
	BCRYPT_KEY_HANDLE       m_hKey			;	
	PBYTE                   m_pbKeyObject	;
	PBYTE                   m_pbIV			;
		 
	bool OpenMSPrimitiveProviderAES();
	bool CreateSymmetricKey_AES_CBC(ULONG &cbKeyObject, ULONG &cbIV );	
	bool Crypt(bool encrypt, std::span<BYTE> in, ULONG iBytesRead, ULONG cbIV, PBYTE out, ULONG& iBufToSave);
	bool CryptLastByte(bool encrypt, std::span<BYTE> in, ULONG iBytesRead, ULONG cbIV, PBYTE out, ULONG& iBufToSave);
			
public:	
	bool CryptFile(bool encrypt, std::string_view in, std::string_view out);
	CNGCryptFile();
	virtual ~CNGCryptFile();
};
