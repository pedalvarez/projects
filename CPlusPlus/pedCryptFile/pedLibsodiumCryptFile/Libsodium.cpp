/*
 * features: https://libsodium.gitbook.io/doc/secret-key_cryptography/secretstream
 *
 * Author(s): pedalvarez@yahoo.com
 */

#include <stdio.h>
#include <sodium.h>

#include "Libsodium.h"
#include <fstream>

static auto open_stream(const std::string& file) -> std::ifstream {
	const auto mode = std::ios_base::in | std::ios_base::binary;
	std::ifstream stream(file, mode);

	if (!stream.is_open())
	{
		std::fprintf(stderr, "Unable to open file %s\n for reading", file.data());
		std::exit(1);
	}
	return stream;
}

static auto open_ostream(const std::string& file) -> std::ofstream {
	const auto mode = std::ios_base::out | std::ios_base::binary;
	std::ofstream stream(file, mode);

	if (!stream.is_open())
	{
		std::fprintf(stderr, "Unable to open file %s\n for writing", file.data());
		std::exit(1);
	}
	return stream;
}

namespace pedalvarez::crypto
{

Libsodium::Libsodium()
{
    if (sodium_init() != 0) 
    {
        throw new std::exception("Failed to initialize crypto library Libsodium!");        
    }
}

Libsodium::~Libsodium()
{

}

bool Libsodium::Encrypt(std::string_view out, std::string_view in)
{
    unsigned char  buf_in[CHUNK_SIZE] = { 0 };
    unsigned char  buf_out[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES] = { 0 };
    unsigned char  header[crypto_secretstream_xchacha20poly1305_HEADERBYTES] = { 0 };
    crypto_secretstream_xchacha20poly1305_state st;

    unsigned long long out_len;

    unsigned char  tag;

    std::streamsize filelength;
    auto file = open_stream(in.data());
    file.seekg(0, std::ios::end);
    filelength = file.tellg();
    file.seekg(std::ios::beg);

    auto outfile = open_ostream(out.data());
    bool ret = true;
    std::streamsize m_iTotalByteRead = 0;

    crypto_secretstream_xchacha20poly1305_init_push(&st, header, key);
    outfile.write((const char*)header, sizeof header);
    while (!file.eof())
    {
        file.read(reinterpret_cast<char*>(buf_in), sizeof buf_in);
        if (file.bad())
        {
            std::fprintf(stderr, "Error reading the file '%s'", in.data());
            ret = false;
            break;
        }

        std::streamsize iBytesRead = ((file) ? sizeof buf_in : file.gcount());
        m_iTotalByteRead += iBytesRead;
        tag = (filelength <= m_iTotalByteRead) ? crypto_secretstream_xchacha20poly1305_TAG_FINAL : 0;

        if (crypto_secretstream_xchacha20poly1305_push(&st, buf_out, &out_len, buf_in, iBytesRead,
            NULL, 0, tag) != 0)
        {
            std::fprintf(stderr, "Failed encrypt chunk.");
            ret = false;
            break;
        }
        outfile.write((char*)buf_out, out_len);
    }
    file.close();
    outfile.close();
    return ret;
}

bool Libsodium::Decrypt(std::string_view out, std::string_view in)
{
    unsigned char  buf_in[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES] = { 0 };
    unsigned char  buf_out[CHUNK_SIZE] = { 0 };
    unsigned char  header[crypto_secretstream_xchacha20poly1305_HEADERBYTES] = { 0 };
    crypto_secretstream_xchacha20poly1305_state st;

    unsigned long long out_len;
    int            ret = true;
    unsigned char  tag;
         
    auto file = open_stream(in.data());
    file.seekg(0, std::ios::end);  // find end of the stream
    std::streamsize filelength = file.tellg();
    file.seekg(std::ios::beg);     // reset stream

    file.read((char*)header, sizeof header);
    if (crypto_secretstream_xchacha20poly1305_init_pull(&st, header, key) != 0)
    {
        std::fprintf(stderr, "Error, imcomplete header.");
        file.close();
        return false;
    }

    auto outfile = open_ostream(out.data());
    std::streamsize TotalByteRead = 0;
    while (!file.eof())
    {
        file.read((char*)buf_in, sizeof buf_in);
        if (file.bad())
        {
            std::fprintf(stderr, "Error reading the file '%s'", in.data());
            ret = false;
            break;
        }

        std::streamsize iBytesRead = ((file) ? sizeof buf_in : file.gcount());
        TotalByteRead += iBytesRead;

        if (crypto_secretstream_xchacha20poly1305_pull(&st, buf_out, &out_len, &tag,
            buf_in, iBytesRead, NULL, 0) != 0) 
        {
            std::fprintf(stderr, "Error, corrupted chunk.");
            ret = false;
            break;
        }
        if (tag == crypto_secretstream_xchacha20poly1305_TAG_FINAL)
        {
            if ((filelength < TotalByteRead))
            {
                std::fprintf(stderr, "Error, end of stream reached before the end of the file.");
                ret = false;
                break;
            }
        }
        else 
        {   /* not the final chunk yet */
            if ((filelength < TotalByteRead))
            {
                std::fprintf(stderr, "Error, end of file reached before the end of the stream.");
                ret = false;
                break; 
            }
        }
        outfile.write((char*)buf_out, out_len);
    }

    file.close();
    outfile.close();
    return ret;
}


bool Libsodium::CryptFile(bool encrypt, std::string_view in, std::string_view out)
{
    if (encrypt)
    {
        return Encrypt(out.data(), in.data());
    }
    else
    {
        return Decrypt(out.data(), in.data());
    }	
}

}