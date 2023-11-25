#include "pedZLib.h"
#include "zlib/zlib.h"
#include <cassert>
#include <stringapiset.h>

std::string Compress(const char* data, size_t dataLen, size_t BufferSize, const std::string& CompressionDict)
{
	// Compress all bytes in the uncompressed buffer, watch out for buffer size...
	// inspired on def method of https://www.zlib.net/zlib_how.html
	if (BufferSize <= 0 || BufferSize >= MaxInflateBuffer)
	{
		return std::string(); // careful, we don't want to smash our stack
	}
	
	// We have all input data and set the z_stream structure accordingly.
	z_stream D_stream = {};
	D_stream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(data));
	D_stream.avail_in = static_cast<const uInt>(dataLen);

	int Err = deflateInit2(&D_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY);
	if (Err < 0)
	{
		return std::string();
	}
	if (!CompressionDict.empty())
	{
		Err = deflateSetDictionary(&D_stream, reinterpret_cast<const Bytef*>(CompressionDict.data()), static_cast<uInt>(CompressionDict.length()));
		if (Err < 0)
		{
			inflateEnd(&D_stream);
			return std::string();
		}
	}

	auto* const tmpBuffer = static_cast<char*>(_malloca(BufferSize));
	std::string Out{};
	// run deflate() on input until output buffer not full, finish compression if all of source has been read in
	do {
		// Output space is provided to deflate() by setting avail_out to the number of available output bytes and next_out to a pointer to that space
		D_stream.next_out = reinterpret_cast<Bytef*>(tmpBuffer);
		D_stream.avail_out = static_cast<uInt>(BufferSize);
		// deflate()'s return values:
		// Z_OK is, well, ok but shoudl not happen here, see below
		// Z_STREAM_END is ok and will be returned for the last call of deflate(). guaranteed by calling deflate() with Z_FINISH until it has no more output
		// Z_STREAM_ERROR is only possible if the stream is not initialized properly. We so that not other part of the application clobbered the memory containing the zlib state
		// Z_BUF_ERROR indicates that deflate() could not consume more input or produce more output. It can be called again with more output space or more available input
		Err = deflate(&D_stream, Z_FINISH);  /* no bad return value */
		assert(Err != Z_STREAM_ERROR);		 /* state not clobbered */
		// Compute how much output deflate() provided on the last call, which is the difference between how much space was provided before the call,
		// and how much output space is still available after the call and save result
		if (tmpBuffer != 0) Out.append(tmpBuffer, BufferSize - D_stream.avail_out);
		// loop is repeated until the last deflate() call fails to fill the provided output buffer.
		// Then deflate() has done as much as it can with the provided input.
		// suppose that deflate() has no more output, but just so happened to exactly fill the output buffer! avail_out is zero, and we can't tell that deflate() has done all it can
		// As far as we know, deflate() has more output for us.
		// So we call it again. In a especial case deflate() could produce no output at all, and avail_out remains unchanged as BufferSize
		// That deflate() call wasn't able to do anything, either consume input or produce output, and so it returns Z_BUF_ERROR
		// However this is not a problem. We finally have the desired indication that deflate() is really done, and so we drop out of the loop
		// With flush set to Z_FINISH, final deflate() call will complete the output stream. Subsequent calls of deflate() would return Z_STREAM_ERROR if it not Z_FINISH
	} while (D_stream.avail_out == 0);

	assert(D_stream.avail_in == 0);     /* all input will be used */

	// Now we check to see if we have already processed all of the input. Flush was set to Z_FINISH, since we used all input at once. 
	// it's guaranteed to get Z_STREAM_END from the last deflate() call, since we ran it until the last chunk of input was consumedand all of the output was generated.
	assert(Err == Z_STREAM_END);        /* stream will be complete */

	_freea(tmpBuffer);

	Err = deflateEnd(&D_stream);
	if (Err < 0)
	{
		return std::string();
	}

	return Out;
}

std::string Decompress(const char* data, size_t dataLen, size_t BufferSize, const std::string& CompressionDict)
{
	// Decompress all bytes in the compressed buffer, watch out for size of the buffer...
	// inspired on inf method of https://www.zlib.net/zlib_how.html
	if (BufferSize <= 0 || BufferSize >= MaxInflateBuffer)
	{
		return std::string(); // careful, we don't want to smash our stack
	}

	// We have all input data and set the z_stream structure accordingly.
	z_stream D_stream = {};
	D_stream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(data));
	D_stream.avail_in = static_cast<uInt>(dataLen);

	int Err = inflateInit2(&D_stream, -MAX_WBITS);
	if (Err < 0)
	{
		return std::string();
	}
	if (!CompressionDict.empty())
	{
		Err = inflateSetDictionary(&D_stream, reinterpret_cast<const Bytef*>(CompressionDict.data()), static_cast<uInt>(CompressionDict.length()));
		if (Err < 0)
		{
			inflateEnd(&D_stream);
			return std::string();
		}
	}

	auto* const tmpBuffer = static_cast<char*>(_malloca(BufferSize));
	std::string Out{};
	// Decompress until deflate ends or end of input buffer. If reached the end of the input, leave the outer loop and report an error (incomplete input)	
	do {
		// run inflate() on input until output buffer not full
		D_stream.avail_out = static_cast<uInt>(BufferSize);
		D_stream.next_out = reinterpret_cast<Bytef*>(tmpBuffer);
		// Run the decompression engine itself. There is no need to adjust the flush parameter, since the zlib format is self - terminating
		// there are return values that we need to pay attention to:
		// Z_DATA_ERROR indicates that inflate() detected an error in the zlib compressed data format, either the data is not a zlib stream, 
		// or that the data was corrupted somewhere along the way since it was compressed.
		// Z_MEM_ERROR, may occur since memory allocation is deferred until inflate() needs it, unlike deflate(), whose memory is allocated at the start by deflateInit().
		// Z_STREAM_ERROR, should not be possible here, but could be checked for as noted above for deflate().
		// Z_BUF_ERROR does not need to be checked for here, since we will loop
		// Z_STREAM_END will be checked for later
		Err = inflate(&D_stream, Z_NO_FLUSH);
		assert(Err != Z_STREAM_ERROR);  // state not clobbered
		switch (Err) {
		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
		case Z_NEED_DICT:			// we have a dictionary so this should not happen
			(void)inflateEnd(&D_stream);
			_freea(tmpBuffer);
			return std::string();
		}
		// calculate how much used, reallocate result buffer and save
		if (tmpBuffer != 0) Out.append(tmpBuffer, BufferSize - D_stream.avail_out);

		// The do - loop ends when inflate() reports that it has reached the end of the input, has completed the decompressionand integrity check,
		// and has provided all of the output.
		// This is indicated by the inflate() return value Z_STREAM_END.
		// if the last chunk of the input read contained the end of the zlib stream.
		// the return value is not Z_STREAM_END, the loop continues to read more input.
		// done when inflate() says it's done
	} while (D_stream.avail_out == 0 && Err != Z_STREAM_END);

	_freea(tmpBuffer);

	Err = inflateEnd(&D_stream);
	if (Err < 0)
	{
		return std::string();
	}
	return Out;
}