/*
 * features: https://libsodium.gitbook.io/doc/secret-key_cryptography/secretstream
 * 
 * Author(s): pedalvarez@yahoo.com
 */
#include <stdio.h>
#include <string>
#include <sodium.h>
#include <fstream>
#include "Libsodium.h"

void printusage(){
	printf("For encrypting the file:\n");
	printf("pedLibsodiumCipherFile /e sourcefile destinationfile\n");
	printf("For decrypting the file:\n");
	printf("pedLibsodiumCipherFile /d sourcefile destinationfile\n");
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

    // unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    //crypto_secretstream_xchacha20poly1305_keygen(key);

    pedalvarez::crypto::Libsodium l;
    auto result = l.CryptFile(m_bEncrypt, argv[2], argv[3]);
    if (result)
    {
        printf("Success, the file %s has been %s to %s", argv[2], m_bEncrypt ? "encrypted" : "decrypted", argv[3]);
    }
    else
    {
        printf("Failure, %s file %s", m_bEncrypt ? "Encrypting" : "Decrypting", argv[2]);
    }
    
	exit(0);
}