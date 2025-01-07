/*
 * features: https://libsodium.gitbook.io/doc/secret-key_cryptography/secretstream
 *
 * Author(s): pedalvarez@yahoo.com
 */
#pragma once
#include <string>

namespace pedalvarez::crypto
{
constexpr int CHUNK_SIZE = 4096;

static const unsigned char key[] =
{
	'P', 'e', 'd', 'r', 'i', 't', 'o', '#',
	'i', 's', '#', 't', 'h', 'e', 's', 't',
	'P', 'e', 'd', 'r', 'i', 't', 'o', '#',
	'i', 's', '#', 't', 'h', 'e', 's', 't'
};

class Libsodium
{
	bool Encrypt(std::string_view target_file, std::string_view source_file);
	bool Decrypt(std::string_view target_file, std::string_view source_file);

public:
	bool CryptFile(bool encrypt, std::string_view in, std::string_view out);
	Libsodium();
	virtual ~Libsodium();
};

}
