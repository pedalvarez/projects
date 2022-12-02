#include "../pedLicLib/licManager.h"

int main(int argc, char* argv[])
{
	printf("\npedLicSystem Serial\n\n");

	RETVALUE lResult = LicManager::RetrieveMachineCode();

	return lResult;
}