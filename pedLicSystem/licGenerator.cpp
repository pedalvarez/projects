#include "pedLicLib/licManager.h"
#include "pedLicLib/base64Encoder.h"
#include "pedLicLib/base64Decoder.h"
#include <iostream>
#include <fstream>
using namespace std;

bool CreateKey(const char * serial, const char* date,const char* who)
{
	    RETVALUE lResult = SUCCESS;

		// Back to buffer
		unsigned char*	lMachineCode = NULL;
		size_t lMachineCodeSize = 0;
		LicManager::String2Buffer(serial, &lMachineCode, &lMachineCodeSize);

		// create date structure
		unsigned char pDate[DATE_DIM];
		pDate[0] = LicManager::char2int(date[0]);
		pDate[1] = LicManager::char2int(date[1]);
		pDate[2] = LicManager::char2int(date[2]);
		pDate[3] = LicManager::char2int(date[3]);
		pDate[4] = LicManager::char2int(date[4]);
		pDate[5] = LicManager::char2int(date[5]);

		// Compute the software key
		unsigned char lSoftwareKey[SOFTWAREKEY_DIM];

		LicManager::ComputeSoftwareKey(lMachineCode,pDate, lSoftwareKey);

		// Print the software key
		char* lSoftwareKeyString = NULL;
		LicManager::Buffer2String(lSoftwareKey, SOFTWAREKEY_DIM, &lSoftwareKeyString);
		
		printf("\nThe software key for the machine code [%s] is: %s\n\n", serial, lSoftwareKeyString);

		std::stringstream ss(lSoftwareKeyString);
			
		Base64Encoder cb64;
		std::ostringstream stream;	
		cb64.Encode(ss,stream);
						
		// TO TEST
		/*Base64Decoder cb642;	
		std::istringstream ins(stream.str());
		std::ostringstream stream2;	
		cb642.Decode(ins,stream2);
		std::string str2 =  stream2.str();	*/
		
		// save to file
		ofstream myfile;
		std::string filename = who;
		filename.append(date);
        myfile.open (filename);
		myfile << stream.str();
		myfile.close();			
		
		return true;
}

int main(int argc, char* argv[])
{	
	RETVALUE lResult = SUCCESS;		
		
	printf("\npedLicSystem license generator\n\n");

	if (argc != 5)
	{		
		printf("Usage is:\n\n");
		printf("licgenerator MachineCode Date Who Key\n\n");
		printf("\tMachineCode: Serial number from the machine there the software is been installed\n");
		printf("\tDate: Date of expiration in format [YYMMDD]\n");
		printf("\tWho: To Whom the key is aimed\n");
		printf("\tKey: Secret Key\n");
	}
	else	
	{
		if (!strcmp(argv[4], "plingpling"))
		{
			CreateKey(argv[1], argv[2], argv[3]);
		}
	} 	

	return 0;
}

