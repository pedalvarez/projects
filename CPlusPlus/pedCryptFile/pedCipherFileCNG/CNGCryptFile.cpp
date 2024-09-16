
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

#include <ntstatus.h>
#include <stdio.h>
#include <bcrypt.h>

#include "CNGCryptFile.h"
#include <fstream>

auto open_stream(const std::string& file) -> std::ifstream {
	const auto mode = std::ios_base::in | std::ios_base::binary;
	std::ifstream stream(file, mode);
		
	if (!stream.is_open())
	{
		std::fprintf(stderr, "Unable to open file %s\n for reading", file.data());
		std::exit(1);
	}
	return stream;
}

auto open_ostream(const std::string& file) -> std::ofstream {
	const auto mode = std::ios_base::out | std::ios_base::binary;
	std::ofstream stream(file, mode);

	if (!stream.is_open()) 
	{
		std::fprintf(stderr, "Unable to open file %s\n for writing", file.data());
		std::exit(1);
	}		
	return stream;
}

CNGCryptFile::CNGCryptFile()
{
	m_hAesAlg = NULL;
	m_hKey = NULL;
	m_pbKeyObject = NULL;
	m_pbIV = NULL;
}

CNGCryptFile::~CNGCryptFile()
{
    if(m_hAesAlg)
    {
        BCryptCloseAlgorithmProvider(m_hAesAlg,0);
    }

    if (m_hKey)    
    {
        BCryptDestroyKey(m_hKey);
    }

    if(m_pbKeyObject)
    {
        HeapFree(GetProcessHeap(), 0, m_pbKeyObject);
    }

    if(m_pbIV!=NULL)
    {
        HeapFree(GetProcessHeap(), 0, m_pbIV);
    }
}

bool CNGCryptFile::CryptFile(bool encrypt, std::string_view in, std::string_view out) 
{	
	NTSTATUS	ntStatus			= STATUS_UNSUCCESSFUL;
	ULONG		cbKeyObject			= 0;
	ULONG		cbIV = 0;
	BYTE		pbufFileToOpen[CHUNK_SIZE];	
	BYTE		pbufFileToSave[CHUNK_SIZE*2];
	
	if (!OpenMSPrimitiveProviderAES())
	{
		return false;
	}

	if (!CreateSymmetricKey_AES_CBC(cbKeyObject, cbIV))
	{
		return false;
	}

	ULONGLONG filelength;
	auto file = open_stream(in.data());
	file.seekg(0, std::ios::end);	
	filelength = file.tellg();
	file.seekg(std::ios::beg);
	bool ret = true;
	auto outfile = open_ostream(out.data());

	ULONG iBufToSave = 0;
	ULONGLONG m_iTotalByteRead = 0;
	while ( !(filelength <= m_iTotalByteRead))
	{			
		iBufToSave=0;				
		file.read(reinterpret_cast<char *>(pbufFileToOpen), CHUNK_SIZE);
		if (file.bad())
		{
			std::fprintf(stderr,"Error reading the file '%s'", in.data());
			ret = false;
			break;			
		}

		std::streamsize iBytesRead = ((file) ? CHUNK_SIZE : file.gcount());
		m_iTotalByteRead += iBytesRead;

		if ( iBytesRead == 0  )
		{			
			std::fprintf(stderr, "Error reading the file '%s'",in.data());
			ret = false;
			break;
		}

		if (!(filelength <= m_iTotalByteRead))
		{
			if (!Crypt(encrypt, pbufFileToOpen, (ULONG)(iBytesRead), cbIV, pbufFileToSave, iBufToSave))
			{
				ret = false;
				break;
			}
			outfile.write((char*)pbufFileToSave,iBytesRead);
		}	
		else 
		{	
			if (!CryptLastByte(encrypt, pbufFileToOpen, (ULONG)iBytesRead, cbIV, pbufFileToSave, iBufToSave))
			{
				ret = false;
				break;
			}
			outfile.write((char*)pbufFileToSave,iBufToSave);
		}
	}
	file.close();
	outfile.close();
	return ret;
}


bool CNGCryptFile::OpenMSPrimitiveProviderAES()
{
	NTSTATUS ntStatus = STATUS_UNSUCCESSFUL;
	ntStatus  = BCryptOpenAlgorithmProvider( &m_hAesAlg, BCRYPT_AES_ALGORITHM, NULL, 0);
	switch (ntStatus)
	{
	case STATUS_SUCCESS:
		return true;
	case STATUS_INVALID_PARAMETER:
		std::fprintf(stderr, "Error. BCryptOpenAlgorithmProvider one or more parameters are not valid. ");
		break;
	case STATUS_NO_MEMORY:
		std::fprintf(stderr, "Error. BCryptOpenAlgorithmProvider a memory allocation failure occurred. ");
		break;
	default:
		std::fprintf(stderr, "Error. BCryptOpenAlgorithmProvider return with error 0x%08x", ntStatus);      
		break;		
	}
	return false;
}

bool CNGCryptFile::Crypt(bool encrypt, std::span<BYTE> in, ULONG iBytesRead, ULONG cbIV, PBYTE out, ULONG& iBufToSave)
{
	NTSTATUS ntStatus =STATUS_UNSUCCESSFUL;	
	ULONG		cbCipherText		= 0;
	if (encrypt)
	{
		ntStatus = BCryptEncrypt(m_hKey, (PUCHAR)in.data(), iBytesRead, NULL, m_pbIV, cbIV, out, iBytesRead, &iBufToSave, 0);
	}
	else
	{
		ntStatus = BCryptDecrypt(m_hKey, (PUCHAR)in.data(), iBytesRead, NULL, m_pbIV, cbIV, out, iBytesRead, &iBufToSave, 0);
	}

	switch(ntStatus)
	{
	case STATUS_SUCCESS:
		return true;
	case STATUS_BUFFER_TOO_SMALL :
		std::fprintf(stderr, "Error %s The size specified by the out parameter is too short to hold the cipher. 0x%08x", encrypt ?"BCryptEncrypt":"BCryptDecrypt",  ntStatus);
		break;		
	case STATUS_INVALID_PARAMETER :
		std::fprintf(stderr, "Error %s One or more parameters are not valid. 0x%08x", encrypt ?"BCryptEncrypt":"BCryptDecrypt",  ntStatus);
		break;
	case STATUS_NOT_SUPPORTED :
		std::fprintf(stderr, "Error %s The algorithm does not support encryption. 0x%08x", encrypt ?"BCryptEncrypt":"BCryptDecrypt",  ntStatus);
		break;
	default:
		std::fprintf(stderr, "Error %s returned 0x%08x", encrypt ?"BCryptEncrypt":"BCryptDecrypt",  ntStatus);
	}
	return false;
}

bool CNGCryptFile::CryptLastByte(bool encrypt, std::span<BYTE> in, ULONG iBytesRead, ULONG cbIV, PBYTE out, ULONG& iBufToSave)
{
	NTSTATUS ntStatus= STATUS_UNSUCCESSFUL;
	ULONG		cbCipherText		= 0;

	if (encrypt)
	{
		ntStatus = BCryptEncrypt(m_hKey, (PUCHAR)in.data(), iBytesRead, NULL, m_pbIV, cbIV, NULL, 0, &cbCipherText, BCRYPT_BLOCK_PADDING);

		if ( ntStatus != STATUS_SUCCESS )
		{
			std::fprintf(stderr, "Error receiving the size required for the ciphertext. BCryptEncrypt returns 0x%08x", ntStatus);					
			return false;
		}
		ntStatus = BCryptEncrypt( m_hKey,(PUCHAR) in.data(), iBytesRead, NULL, m_pbIV, cbIV, out, cbCipherText, &cbCipherText, BCRYPT_BLOCK_PADDING);
		switch(ntStatus)
		{
		case STATUS_SUCCESS:			
			iBufToSave		=	cbCipherText;
			return true;
		default:					
			std::fprintf(stderr, "Error receiving ciphertext. BCryptEncrypt returns 0x%08x", ntStatus);					
			return false;
		}
	}
	else
	{
		ntStatus = BCryptDecrypt( m_hKey, (PUCHAR)in.data(), iBytesRead, NULL, m_pbIV, cbIV, NULL, 0, &cbCipherText, BCRYPT_BLOCK_PADDING);

		if ( ntStatus != STATUS_SUCCESS )
		{
			std::fprintf(stderr, "Error receiving the size required for the ciphertext. BCryptDecrypt returns 0x%08x", ntStatus);					
			return false;
		}	
		ntStatus = BCryptDecrypt( m_hKey, (PUCHAR)in.data(), iBytesRead, NULL, m_pbIV, cbIV, out, cbCipherText, &cbCipherText, BCRYPT_BLOCK_PADDING);

		switch(ntStatus)
		{
		case STATUS_SUCCESS:			
			iBufToSave = cbCipherText;
			return true;
		default:
			std::fprintf(stderr, "Error receiving ciphertext. BCryptDecrypt returns 0x%08x", ntStatus);					
			return false;
		}
	}
	return false;
}

bool CNGCryptFile::CreateSymmetricKey_AES_CBC(ULONG &cbKeyObject, ULONG &cbIV )
{
	NTSTATUS	ntStatus = STATUS_UNSUCCESSFUL;
	ULONG		cbData	= 0; 

	cbKeyObject	= 0;
	cbIV  = 0;

	ntStatus = BCryptGetProperty(m_hAesAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbKeyObject,  sizeof(ULONG), &cbData, 0);
	if (ntStatus!=STATUS_SUCCESS)
	{
		std::fprintf(stderr, "Error calculating the size of KeyObject. BCryptGetProperty returns 0x%08x", ntStatus);
		return false;
	}
	
	m_pbKeyObject = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbKeyObject);
	if(NULL == m_pbKeyObject)
	{
		std::fprintf(stderr, "Error memory allocation key object on the heap failed");
		return false;
	}

	ntStatus = BCryptGetProperty( m_hAesAlg, BCRYPT_BLOCK_LENGTH, (PBYTE)&cbIV, sizeof(ULONG), &cbData, 0);
	if (ntStatus!=STATUS_SUCCESS)
	{
		std::fprintf(stderr, "Error calculating the block length for the IV. BCryptGetProperty return with error 0x%08x", ntStatus);
		return false;
	}

	if (cbIV > sizeof (rgbIV))
	{
		std::fprintf(stderr, "Block length is longer than the provided IV length\n");
		return false;
	}

	m_pbIV= (PBYTE) HeapAlloc (GetProcessHeap (), 0, cbIV);
	if(NULL == m_pbIV)
	{
		std::fprintf(stderr, "Error memory allocation buffer for the IV on the heap failed");
		return false;
	}

	memcpy(m_pbIV, rgbIV, cbIV);

	ntStatus = BCryptSetProperty(m_hAesAlg, BCRYPT_CHAINING_MODE, (PBYTE)BCRYPT_CHAIN_MODE_CBC, sizeof(BCRYPT_CHAIN_MODE_CBC), 0);
	if (ntStatus!=STATUS_SUCCESS)
	{
		std::fprintf(stderr, "Error setting the ChainingMode CBC. BCryptSetProperty return with error 0x%08x", ntStatus);
		return false;
	}

	// generate the key from supplied input key bytes
	ntStatus = BCryptGenerateSymmetricKey(m_hAesAlg, &m_hKey, m_pbKeyObject, cbKeyObject, (PBYTE)Aes128Password, sizeof(Aes128Password), 0);

	if (ntStatus!=STATUS_SUCCESS)
	{
		std::fprintf(stderr, "Error generate the key. BCryptGenerateSymmetricKey return with error 0x%08x", ntStatus);
		return false;
	}

	return true;
}