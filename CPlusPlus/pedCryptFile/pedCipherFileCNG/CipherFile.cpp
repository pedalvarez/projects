/*
 * features: Idea from https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Security/CipherEncryptionDecryption/cpp/CipherEncryptionDecryption.cpp
 *  
 */
#include <stdio.h>
#include <windows.h>
#include <string>
#include "CNGCryptFile.h"

void printusage(){
	printf("For encrypting the file:\n");
	printf("pedCipherFile /e sourcefile destinationfile\n");
	printf("For decrypting the file:\n");
	printf("pedCipherFile /d sourcefile destinationfile\n");
	exit(0);
}
 
int main(int argc, char* argv[])
{
    bool m_bEncrypt = false;

    if (argc == 4)
    {
        if (!strcmp(argv[1],"-e") || !strcmp(argv[1],"/e") )
        {
            m_bEncrypt = true;
        }
        else if (strcmp(argv[1], "-d") && strcmp(argv[1], "/d"))
        {
            printusage();
        }
    }
    else
    {
        printusage();
    }

    CNGCryptFile oCngAes;
    if (oCngAes.CryptFile(m_bEncrypt, std::string{ argv[2] }, std::string{ argv[3] }))
    {
        printf("Success, the file %s is %s", m_bEncrypt ? "Encrypted" : "Decrypted", argv[3]);
    }
	exit(0);
}