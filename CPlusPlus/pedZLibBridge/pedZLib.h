#pragma once

#include <windows.h>
#include <string>

static const size_t MaxInflateBuffer = 128 * 1024;

std::string Compress(const char* data, size_t dataLen, size_t BufferSize, const std::string& CompressionDict);
std::string Decompress(const char* data, size_t dataLen, size_t BufferSize, const std::string& CompressionDict);