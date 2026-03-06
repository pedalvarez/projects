#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

namespace {
constexpr __int64 kInitialTailBytes = 512;
constexpr size_t kChunkSize = 1024;
constexpr DWORD kPollDelayMs = 5000;

__int64 get_file_size(FILE* stream)
{
    return _filelengthi64(_fileno(stream));
}

bool seek_to_offset(FILE* stream, __int64 offset)
{
    return _fseeki64(stream, offset, SEEK_SET) == 0;
}

bool write_range(FILE* stream, __int64 bytes_to_write)
{
    static unsigned char buffer[kChunkSize];

    while (bytes_to_write > 0)
    {
        const size_t request = bytes_to_write > static_cast<__int64>(kChunkSize)
            ? kChunkSize
            : static_cast<size_t>(bytes_to_write);

        const size_t bytes_read = fread(buffer, 1, request, stream);
        if (bytes_read != request)
        {
            printf("error reading file\n");
            return false;
        }

        const size_t bytes_written = fwrite(buffer, 1, bytes_read, stdout);
        if (bytes_written != bytes_read)
        {
            printf("error writing output\n");
            return false;
        }

        bytes_to_write -= static_cast<__int64>(bytes_written);
    }

    fflush(stdout);
    return true;
}

FILE* open_input(const char* filename)
{
    FILE* stream = fopen(filename, "rb");
    if (stream == NULL)
    {
        printf("Unable to open input file %s (errno=%d)\n\n", filename, errno);
    }

    return stream;
}
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Simple binary 'Tail' program for Windows.\n");
        printf("Usage: pedTail <input file> \n\n");
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];

    FILE* stream = open_input(filename);
    if (stream == NULL)
    {
        return EXIT_FAILURE;
    }

    __int64 known_size = get_file_size(stream);
    __int64 initial_bytes = known_size > kInitialTailBytes ? kInitialTailBytes : known_size;
    const __int64 initial_offset = known_size - initial_bytes;

    if (!seek_to_offset(stream, initial_offset))
    {
        printf("Unable to seek to offset %lld\n", initial_offset);
        fclose(stream);
        return EXIT_FAILURE;
    }

    printf("Starting at offset %lld\n\n", initial_offset);

    if (!write_range(stream, initial_bytes))
    {
        fclose(stream);
        return EXIT_FAILURE;
    }

    fclose(stream);

    while (true)
    {
        Sleep(kPollDelayMs);

        stream = open_input(filename);
        if (stream == NULL)
        {
            return EXIT_FAILURE;
        }

        const __int64 current_size = get_file_size(stream);

        if (current_size < known_size)
        {
            // File was truncated/rotated; restart by showing the last window.
            known_size = current_size > kInitialTailBytes ? kInitialTailBytes : current_size;
            const __int64 reset_offset = current_size - known_size;

            if (!seek_to_offset(stream, reset_offset) || !write_range(stream, known_size))
            {
                fclose(stream);
                return EXIT_FAILURE;
            }

            known_size = current_size;
            fclose(stream);
            continue;
        }

        const __int64 delta = current_size - known_size;
        if (delta > 0)
        {
            if (!seek_to_offset(stream, known_size) || !write_range(stream, delta))
            {
                fclose(stream);
                return EXIT_FAILURE;
            }

            known_size = current_size;
        }

        fclose(stream);
    }
}
