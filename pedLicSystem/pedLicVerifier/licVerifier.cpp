#include <iostream>
#include <fstream>
#include <string>
#include "../pedLicLib/licManager.h"
#include "../pedLicLib/base64Decoder.h"
#include <ObjBase.h>

int main(int argc, char* argv[])
{
	printf("\npedLicSystem verifier\n\n");

	if (argc != 2)
	{
		printf("Usage is:\n\n");
		printf("licCheckTest file\n\n");
		printf("\tfile: license file\n");
		return 0;
	}	

	// Get the software key from the file
	std::string line;
	std::ifstream myfile (argv[1]);
	if (myfile.is_open())
	{
		getline (myfile,line);
		myfile.close();
	}
	else {
		std::cout << "Unable to open license file\n";
		return 1;
	}

	// decode
	Base64Decoder cb64;
	std::istringstream ins(line.c_str());
	std::ostringstream stream;
	cb64.Decode(ins,stream);
	std::string str =  stream.str();	// = argv[1];

	// Verify
	bool lIsValid = false;
	RETVALUE lResult = LicManager::VerifySoftwareKey(str.c_str(), &lIsValid);

	if (!lIsValid)
	{
		std::cout <<  "Wrong software key!\n";
		return 1;
	}

	std::cout << "Correct software key installed";
	return 0;
}