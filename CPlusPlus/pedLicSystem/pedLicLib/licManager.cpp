#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "licmanager.h"   

// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

int LicManager::char2int(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;

	return 0;
}

void LicManager::hex2bin(const char* src, unsigned char* target)
{
	while (*src && src[1])
	{
		*(target++) = char2int(*src) * 16 + char2int(src[1]);
		if (src[2])
			src += 3;
		else
			src += 2;
	}
}

RETVALUE LicManager::RetrieveMachineCode(){

	RETVALUE lResult = SUCCESS;
		
	// retrieve HD serial (No used, but printed anyways)
	DWORD dwVolSerial;
	bool bIsRetrieved = GetVolumeInformation(NULL, NULL, NULL, &dwVolSerial, NULL, NULL, NULL, NULL);
	
	if (bIsRetrieved)
	{
		printf("Serial number of drive is %X\n",dwVolSerial);

		std::ostringstream stream;
   
		stream << dwVolSerial;
		std::string str = stream.str();
	}
	else
	{
		printf("Could not retrieve Serail number of drive c\n");
	}
			
	// Retrieve the MAC address
	unsigned char lMACaddress[MAC_DIM]= {0};		
	lResult = RetrieveMACAddress(lMACaddress);

	// Compute the machine code
	unsigned char lMachineCode[MACHINE_CODE_DIM]= {0};
	lResult = ComputeSerialNumber( lMACaddress, lMachineCode);
		
	char* lMachineCodeString = NULL;
	Buffer2String( lMachineCode, MACHINE_CODE_DIM, &lMachineCodeString);
	printf("\nThe machine code is: %s\n\n", lMachineCodeString);
	delete lMachineCodeString;

	return lResult;
}

void LicManager::ComputeSoftwareKey(const unsigned char pMachineCode[MACHINE_CODE_DIM], 
									const unsigned char pDate[DATE_DIM], 
									unsigned char pSoftwareKey[SOFTWAREKEY_DIM])
{
	pSoftwareKey[0] = pMachineCode[1];
	pSoftwareKey[1] = pDate[5];
	pSoftwareKey[2] = pMachineCode[4];
	pSoftwareKey[3] = pDate[2];
	pSoftwareKey[4] = pMachineCode[3];
	pSoftwareKey[5] = pDate[4];
	pSoftwareKey[6] = pMachineCode[2];
	pSoftwareKey[7] = pDate[3];
	pSoftwareKey[8] = pMachineCode[5];
	pSoftwareKey[9] = pDate[1];
	pSoftwareKey[10] = pMachineCode[0];				
	pSoftwareKey[11] = pDate[0];
}

RETVALUE LicManager::VerifySoftwareKey(const char* pSoftwareKeyString, bool* pIsValid)
{
	RETVALUE		lReturnValue = SUCCESS;
	bool			lIsValid = false;
    
	unsigned char lMACaddress[MAC_DIM] = {0};	
	lReturnValue = RetrieveMACAddress(lMACaddress);

	unsigned char lMachineCode[MACHINE_CODE_DIM] = { 0 };
	lReturnValue = ComputeSerialNumber(lMACaddress, lMachineCode);		

	// Date if allways part of the software key...get it from there
	unsigned char*	lDate = NULL;
	size_t	lDateSize = 0;	
	LicManager::String2Buffer(pSoftwareKeyString, &lDate, &lDateSize); 
	
	unsigned char date[DATE_DIM];
	date[0] = lDate[11];
	date[1] = lDate[9];
	date[2] = lDate[3];
	date[3] = lDate[7];
	date[4] = lDate[5];
	date[5] = lDate[1];
	
	unsigned char lSoftwareKey[SOFTWAREKEY_DIM];
	ComputeSoftwareKey(lMachineCode, date, lSoftwareKey); 

	char* lSoftwareKeyString = NULL;
	Buffer2String(lSoftwareKey, SOFTWAREKEY_DIM, &lSoftwareKeyString);
		
	// verify
	size_t lSoftwareKeyStringLen = strlen(lSoftwareKeyString);
	if (lSoftwareKeyStringLen == strlen(pSoftwareKeyString))
	{
		bool checkall = true;
		for (unsigned int i = 0; i<lSoftwareKeyStringLen; i++)
		{
			unsigned char lKey1 = lSoftwareKeyString[i];
			unsigned char lKey2 = pSoftwareKeyString[i];

			if (lKey1 != lKey2)
			{
				checkall = false;
				break;
			}
		}
		lIsValid = checkall;
	}
	delete lSoftwareKeyString;

	// check date
	if (lIsValid)
	{
		int datesum = date[0] + date[1] + date[2] + date[3] + date[4] + date[5];
		printf("License date sum: %i\n", datesum);

		std::time_t rawtime;
		std::tm timeinfo;
		char buffer[80];
		std::time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		std::strftime(buffer, 80, "%y%m%d", &timeinfo);
		std::puts(buffer);

		unsigned char lDateNow[DATE_DIM]={0,0,0,0,0,0};
		char lAppString[2];
		for (unsigned int i = 0; i < DATE_DIM; i++)
		{
			sprintf_s(lAppString,2, "%c", buffer[i]);
			unsigned char b = (unsigned char)atoi(lAppString);
			lDateNow[i] = b;
		}
		int datesumNow = lDateNow[0] + lDateNow[1] + lDateNow[2] + lDateNow[3] + lDateNow[4] + lDateNow[5];
		printf("Now date sum: %i\n", datesumNow);

		if (datesumNow > datesum)
		{
			lIsValid = false;
			lReturnValue = LICENSE_EXPIRED;
			printf("License expired\n");
		}
	}
	
	*pIsValid = lIsValid;
	return lReturnValue;
}

void LicManager::Buffer2String(	const unsigned char* pBuffer, const unsigned int pBufferSize, char** pString)
{	
	unsigned int lOutStringSize = (pBufferSize*3) + 1;
	
	// it is the caller that it is on charge to delete this pointer
	char* lOutString = new char[lOutStringSize];
	sprintf_s(lOutString, lOutStringSize,"%s","");

	char lAppString[4];
	for (unsigned int i = 0; i < pBufferSize; i++)
	{
		unsigned char b = pBuffer[i];
		// NOTE: 3 chars in out string for each byte in input buffer
		sprintf_s(lAppString,4,"%03u",b); 
		strcat_s(lOutString, lOutStringSize,lAppString);
	}
	*pString = lOutString;		
}

void LicManager::String2Buffer(const char*	pString,
								unsigned char**	pBuffer, 
								size_t*	pBufferSize)
{	
	size_t	lOutBufferSize = strlen(pString) / 3;
	
	// it is the caller that it is on charge to delete this pointer
	unsigned char*	lOutBuffer = new unsigned char[lOutBufferSize];	

	char lAppString[4];

	unsigned int j	= 0;
	unsigned int j1 = 0;
	unsigned int j2 = 0;
	unsigned int j3 = 0;

	for (unsigned int i = 0; i < lOutBufferSize; i++)
	{
		j1 = j++;
		j2 = j++;
		j3 = j++;
		sprintf_s(lAppString,4,"%c%c%c",pString[j1],pString[j2],pString[j3]);
		// NOTE: one byte in output buffer for each 3 chars in input string
		unsigned char b = (unsigned char) atoi(lAppString);
		lOutBuffer[i] = b;
	}	
	*pBuffer = lOutBuffer;
	*pBufferSize = lOutBufferSize;
}

RETVALUE LicManager::ComputeSerialNumber(
									const unsigned char pMACaddress[MAC_DIM], 
									unsigned char pMachineCode[6])
{
	RETVALUE		lReturnValue = SUCCESS;

	pMachineCode[0] = pMACaddress[5];
	pMachineCode[1] = pMACaddress[0];
	pMachineCode[2] = pMACaddress[2];
	pMachineCode[3] = pMACaddress[1];
	pMachineCode[4] = pMACaddress[3];
	pMachineCode[5] = pMACaddress[4];
	
	return lReturnValue;
}

RETVALUE LicManager::RetrieveMACAddress(unsigned char pMACaddress[MAC_DIM])
{
	RETVALUE ret = ERROR_API_CALL_FAILED;

    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
    unsigned int i = 0;

    // Set the flags to pass to GetAdaptersAddresses
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

    // default to unspecified address family (both)
    ULONG family = AF_UNSPEC;
	    
    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    ULONG outBufLen = 0;
    ULONG Iterations = 0;

    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
    IP_ADAPTER_PREFIX *pPrefix = NULL;
    
    // Allocate a 15 KB buffer to start with.
    outBufLen = WORKING_BUFFER_SIZE;

    do {
        pAddresses = (IP_ADAPTER_ADDRESSES *) MALLOC(outBufLen);
        if (pAddresses == NULL) 
		{
            printf ("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
            return ret;
        }

        dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

        if (dwRetVal == ERROR_BUFFER_OVERFLOW) 
		{
            FREE(pAddresses);
            pAddresses = NULL;
        }
		else 
		{
            break;
        }

        Iterations++;

    } while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

    if (dwRetVal == NO_ERROR)
	{
        pCurrAddresses = pAddresses;
        while (pCurrAddresses)
		{            
			if (pCurrAddresses->IfType != IF_TYPE_SOFTWARE_LOOPBACK  && pCurrAddresses->PhysicalAddressLength != 0) 
			{
		        printf("\tPhysical address: ");
                for (i = 0; i < (int) pCurrAddresses->PhysicalAddressLength && i < MAC_DIM;
                     i++) {                    
                        printf("%.2X\n",
                               (int) pCurrAddresses->PhysicalAddress[i]);

		                pMACaddress[i]  = (int) pCurrAddresses->PhysicalAddress[i];
                }				
				ret= SUCCESS;
				break;				
            }
            pCurrAddresses = pCurrAddresses->Next;
        }
    } 
	else
	{
        printf("Call to GetAdaptersAddresses failed with error: %d\n",  dwRetVal);
        if (dwRetVal == ERROR_NO_DATA)
            printf("\tNo addresses were found for the requested parameters\n");
        else 
		{
			LPSTR lpMsgBuf = NULL;
            if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
                    NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   
                    // Default language
                    (LPTSTR) & lpMsgBuf, 0, NULL)) {
                printf("\tError: %s", lpMsgBuf);
                LocalFree(lpMsgBuf);                
            }
        }
    }

    if (pAddresses)
	{
        FREE(pAddresses);
    }

	return ret;
}