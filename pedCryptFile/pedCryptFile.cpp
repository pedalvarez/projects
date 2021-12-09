/*
 * features: Merge to MSDN examples into a program
 *           own ErrorHandler logs to pedCryptfile.log in the current directory
 *           Retry CryptAcquireContext with CRYPT_NEWKEYSET if NTE_BAD_KEYSET
 * 
 * Author(s): pedalvarez@yahoo.com
 */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <wincrypt.h>
#include <stdlib.h>

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

char logpath[MAX_PATH];

// The following additional #define statements are required.
#define ENCRYPT_ALGORITHM CALG_RC4 
constexpr auto ENCRYPT_BLOCK_SIZE = 8 ;
constexpr auto KEYLENGTH = 0x00800000;

void ErrorHandler(const char* s) {
    char buf[521];
    sprintf_s(buf, "Error, %s,(%x).\n", s, GetLastError());
    fprintf(stderr, buf);
    FILE* f;
    errno_t err = fopen_s(&f, logpath, "a+");
    if (errno == 0 && f != 0) {
        fprintf(f, "%s\n", buf);
        fclose(f);
    }
    exit(1);
}

static void EncryptFile(FILE* hSource, FILE* hDestination, PCHAR szPassword) {
    HCRYPTPROV hCryptProv;
    HCRYPTKEY hKey, hXchgKey;
    HCRYPTHASH hHash;
    PBYTE pbKeyBlob, pbBuffer;
    DWORD dwKeyBlobLen, dwBlockLen, dwBufferLen;
    if (CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0)) {
        printf("A cryptographic provider has been acquired. \n");
    }
    else
    {
        if (GetLastError() == NTE_BAD_KEYSET) {
            if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
                ErrorHandler("CryptAcquireContext with new key set");
            }
            else {
                printf("A cryptographic provider has been acquired. \n");
            }
        }
        else {
            ErrorHandler("CryptAcquireContext");
        }
    }
    
    if (!szPassword)
    {   // No password was passed. Encrypt with a random session key, and write the key to a file        
        if (CryptGenKey(hCryptProv, ENCRYPT_ALGORITHM, KEYLENGTH | CRYPT_EXPORTABLE, &hKey)) {
            printf("A session key has been created. \n");
        }
        else {
            ErrorHandler("CryptGenKey");
        }
        // Get the handle to the encrypter's exchange public key
        if (CryptGetUserKey(hCryptProv, AT_KEYEXCHANGE, &hXchgKey)) {
            printf("The user public key has been retrieved. \n");
        }
        else {
            ErrorHandler("User public key is not available and may not exist");
        }
        // Determine size of the key BLOB, and allocate memory
        if (CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwKeyBlobLen)) {
            printf("The key BLOB is %d bytes long. \n", dwKeyBlobLen);
        }
        else {
            ErrorHandler("Computing BLOB length");
        }
        if (pbKeyBlob = (BYTE*)malloc(dwKeyBlobLen)) {
            printf("Memory is allocated for the key BLOB. \n");
        }
        else {
            ErrorHandler("Out of memory");
        }
        // Encrypt and export the session key into a simple key BLOB
        if (CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwKeyBlobLen)) {
            printf("The key has been exported. \n");
        }
        else {
            ErrorHandler("CryptExportKey");
        }
        // Release the key exchange key handle. 
        if (hXchgKey) {
            if (!(CryptDestroyKey(hXchgKey)))
                ErrorHandler("CryptDestroyKey");
            hXchgKey = 0;
        }
        // Write the size of the key BLOB to a destination file.
        fwrite(&dwKeyBlobLen, sizeof(DWORD), 1, hDestination);
        if (ferror(hDestination)) {
            ErrorHandler("Writing header.");
        }
        else {
            printf("A file header has been written. \n");
        }
        // Write the key BLOB to a destination file.      
        fwrite(pbKeyBlob, 1, dwKeyBlobLen, hDestination);
        if (ferror(hDestination)) {
            ErrorHandler("Writing header");
        }
        else {
            printf("The key BLOB has been written to the file. \n");
        }
        free(pbKeyBlob);
    }
    else {
        // The file will be encrypted with a session key derived from a password. the session key will 
        // be recreated when the file is decrypted only if the password used to create the key is available
        if (CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash)) {
            printf("A hash object has been created. \n");
        }
        else {
            ErrorHandler("CryptCreateHash");
        }
        // Hash the password. 
        if (CryptHashData(hHash, (BYTE*)szPassword, strlen(szPassword), 0)) {
            printf("The password has been added to the hash. \n");
        }
        else {
            ErrorHandler("CryptHashData");
        }
        // Derive a session key from the hash object. 
        if (CryptDeriveKey(hCryptProv, ENCRYPT_ALGORITHM, hHash, KEYLENGTH, &hKey)) {
            printf("An encryption key is derived from the password hash. \n");
        }
        else {
            ErrorHandler("CryptDeriveKey");
        }
        // Destroy hash object. 
        if (hHash) {
            if (!(CryptDestroyHash(hHash)))
                ErrorHandler("CryptDestroyHash");
            hHash = 0;
        }
    }

    // The session key is ready. If it is not a key derived from a password, the session key encrypted with the encrypter's private 
    // key has been written to the destination file. Determine the number of bytes to encrypt at a time. 
    // This must be a multiple of ENCRYPT_BLOCK_SIZE which is set by a #define statement.
    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

    // Determine the block size. If a block cipher is used, it must have room for an extra block
    if (ENCRYPT_BLOCK_SIZE > 1)
        dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;
    else
        dwBufferLen = dwBlockLen;

    if (pbBuffer = (BYTE*)malloc(dwBufferLen)) {
        printf("Memory has been allocated for the buffer. \n");
    }
    else {
        ErrorHandler("Out of memory");
    }

    if (hSource && hDestination) {
        do
        {   // Read up to dwBlockLen bytes from the source file. 
            DWORD dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);
            if (ferror(hSource)) {
                ErrorHandler("Reading source file");
            }
            // Encrypt data. 
            if (!CryptEncrypt(hKey, 0, feof(hSource), 0, pbBuffer, &dwCount, dwBufferLen)) {
                ErrorHandler("CryptEncrypt");
            }
            // Write data to the destination file. 
            fwrite(pbBuffer, 1, dwCount, hDestination);
            if (ferror(hDestination)) {
                ErrorHandler("Writing to destination file");
            }
        } while (!feof(hSource));

        if (fclose(hSource))
            ErrorHandler("Closing source file");
        if (fclose(hDestination))
            ErrorHandler("Closing destination file");
    }

    if (pbBuffer)
        free(pbBuffer);
    if (hKey) {
        if (!(CryptDestroyKey(hKey)))
            ErrorHandler("CryptDestroyKey");
    }
    if (hCryptProv) {
        if (!(CryptReleaseContext(hCryptProv, 0)))
            ErrorHandler("CryptReleaseContext");
    }
}

static void DecryptFile(FILE* hSource, FILE* hDestination, PCHAR szPassword) {
    HCRYPTPROV hCryptProv;
    HCRYPTKEY hKey;
    HCRYPTHASH hHash;
    PBYTE pbKeyBlob = NULL, pbBuffer;
    DWORD dwKeyBlobLen, dwBlockLen, dwBufferLen;

    if (CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0)) {
        printf("A cryptographic provider has been acquired. \n");
    }
    else {
        if (GetLastError() == NTE_BAD_KEYSET) {
            if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
                ErrorHandler("CryptAcquireContext with new keyset");
            }
        }
        else {
            ErrorHandler("CryptAcquireContext");
        }
    }

    if (!szPassword)
    {    // Decrypt the file with the saved session key.        
        fread(&dwKeyBlobLen, sizeof(DWORD), 1, hSource);
        if (ferror(hSource) || feof(hSource)) {
            ErrorHandler("Reading file header");
        }
        if (!(pbKeyBlob = (BYTE*)malloc(dwKeyBlobLen))) {
            ErrorHandler("Memory allocation error");
        }
        // Read key BLOB from source file.
        fread(pbKeyBlob, 1, dwKeyBlobLen, hSource);
        if (ferror(hSource) || feof(hSource))
        {
            ErrorHandler("Reading file header");
        }
        // Import key BLOB into CSP. 
        if (!CryptImportKey(hCryptProv, pbKeyBlob, dwKeyBlobLen, 0, 0, &hKey)) {
            ErrorHandler("CryptImportKey");
        }
    }
    else
    {   // Decrypt the file with a session key derived from a password        
        if (!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash)) {
            ErrorHandler("CryptCreateHash");
        }
        // Hash in the password data. 
        if (!CryptHashData(hHash, (BYTE*)szPassword, strlen(szPassword), 0)) {
            ErrorHandler("CryptHashData");
        }
        // Derive a session key from the hash object. 
        if (!CryptDeriveKey(hCryptProv, ENCRYPT_ALGORITHM, hHash, KEYLENGTH, &hKey)) {
            ErrorHandler("CryptDeriveKey");
        }
        // Destroy the hash object. 
        if (!(CryptDestroyHash(hHash)))
            ErrorHandler("CryptDestroyHash");
        hHash = 0;
    }
    // The decryption key is now available, either having been imported from a BLOB read in 
    // from the source file or having been created using the password. 
    // This point in the program is not reached if the decryption key is not available.     
    // Determine the number of bytes to decrypt at a time. Must be a multiple of ENCRYPT_BLOCK_SIZE.
    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;
    dwBufferLen = dwBlockLen;

    if (!(pbBuffer = (BYTE*)malloc(dwBufferLen))) {
        ErrorHandler("Out of memory");
    }
    do {// Read up to dwBlockLen bytes from source file
        DWORD dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);
        if (ferror(hSource)) {
            ErrorHandler("Reading source file");
        }
        if (!CryptDecrypt(hKey, 0, feof(hSource), 0, pbBuffer, &dwCount)) {
            ErrorHandler("CryptDecrypt");
        }
        fwrite(pbBuffer, 1, dwCount, hDestination);
        if (ferror(hDestination)) {
            ErrorHandler("Writing to destination file");
        }
    } while (!feof(hSource));

    if (hSource) {
        if (fclose(hSource))
            ErrorHandler("Closing source file");
    }
    if (hDestination) {
        if (fclose(hDestination))
            ErrorHandler("Closing destination file");
    }

    if (pbKeyBlob)
        free(pbKeyBlob);

    if (pbBuffer)
        free(pbBuffer);

    if (hKey) {
        if (!(CryptDestroyKey(hKey)))
            ErrorHandler("CryptDestroyKey");
    }

    if (hCryptProv) {
        if (!(CryptReleaseContext(hCryptProv, 0)))
            ErrorHandler("CryptReleaseContext");
    }
}

void printusage(){
	printf("For encrypting the file:\n");
	printf("pedCryptFile /e sourcefile destinationfile password\n");
	printf("For decrypting the file:\n");
	printf("pedCryptFile /d sourcefile destinationfile password\n");
	exit(0);
}
 
int main(int argc, char* argv[]){ 	
    CHAR szSource[MAX_PATH]; 
    CHAR szDestination[MAX_PATH]; 
    CHAR szPassword[100] = ""; 
	bool b_dec=false;	
    	
	if (argc==5 && (*(argv[1]) == '/') || (*(argv[1]) == '-')) {
        char buf[80];
		strcpy_s(buf,argv[1]);
		CharLowerBuff(buf,strlen(buf));
		if (!strcmp(buf+1,"e")) {
			b_dec=false;
		}
		else if(!strcmp(buf+1,"d")) {
			b_dec=true;
		}
		else{
			printusage();
		}
	}
	else{
		printusage();
	}

	strcpy_s(szSource,argv[2]);
	strcpy_s(szDestination,argv[3]);
	strcpy_s(szPassword,argv[4]);

	char * pdest=strchr(szSource,'\\');  // Get path from source file
	char * ptmp=NULL;
	while(pdest){
		ptmp=pdest;
		pdest=strchr(pdest+1,'\\');
	}
	if(ptmp){
		strncpy_s(logpath,szSource,ptmp-szSource+1);
		logpath[szSource,ptmp-szSource+1]='\0';
		strcat_s(logpath,"pedcryptfile.log");
	}
	else
		strcpy_s(logpath,"pedcryptfile.log");

    FILE* hSource;
    FILE* hDestination;
    errno_t err;
    if (err = fopen_s(&hSource, szSource, "rb") != 0) {
        printf("The source plaintext file, %s, is open. \n", szSource);
    }
    else {
        ErrorHandler("Opening source file");
    }
    if (err = fopen_s(&hDestination, szDestination, "wb") != 0) {
        printf("Destination file %s is open. \n", szDestination);
    }
    else {
        ErrorHandler("Opening destination file");
    }
 
	if(b_dec){
		printf("Decrypt a file. \n\n");
        DecryptFile(hSource, hDestination, szPassword);			
		printf("\nDecryption of file %s succeeded. \n", szSource);
		printf("The decrypted file is %s .\n",szDestination);		
	}
	else{
		printf("Encrypt a file. \n\n");
        EncryptFile(hSource, hDestination, szPassword);
		printf("Encryption of the file %s was a success. \n", szSource);
		printf("The encrypted data is in file %s.\n",szDestination);		
    }
	exit(0);
} // end main