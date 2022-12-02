#if !defined(LICMANAGER_H)   
#define LICMANAGER_H

#include <string>

#define MAC_DIM					6
#define MACHINE_CODE_DIM		6
#define SOFTWAREKEY_DIM			12
#define DATE_DIM				6

enum RETVALUE
{
	SUCCESS,
	LICENSE_EXPIRED,
	ERROR_API_CALL_FAILED,
	ERROR_OS_VERSION_NOT_SUPPORTED
};

class LicManager
{
public:		
	static RETVALUE RetrieveMachineCode();

	static RETVALUE VerifySoftwareKey( const char* pSoftwareKeyString,
									   bool*       pIsValid);

	static void     ComputeSoftwareKey(	const unsigned char	pMachineCode[MACHINE_CODE_DIM],
										const unsigned char	pDate[DATE_DIM],
										unsigned char pSoftwareKey[SOFTWAREKEY_DIM]);

	static void		String2Buffer( const char*		pString,
						           unsigned char**	pBuffer,
						           size_t*	pBufferSize);

	static void		Buffer2String( const unsigned char* pBuffer,
						           const unsigned int	pBufferSize,
						           char**				pString);

	static int		char2int(char input);

private:

	static RETVALUE RetrieveMACAddress(	unsigned char	pMACaddress[MAC_DIM]);

	static RETVALUE ComputeSerialNumber( const unsigned char pMACaddress[MAC_DIM],
						                 unsigned char		 pMachineCode[MACHINE_CODE_DIM]);

	static void		hex2bin(const char* src, unsigned char* target);
};

#endif