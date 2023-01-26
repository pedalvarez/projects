#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <Windows.h>

void  main(int argc, char* argv[])
{
	if ( argc != 2)
	{
		printf("Simple binary 'Tail' program for Windows.\n");
		printf("Usage: pedTail <input file> \n\n");
		return;
	}
	
	char* v_FileName_in = (char*)argv[1];
	
	__int64 v_size = 512;
    
	#define CHUNK_SIZE 1024
	static char v_buffer[CHUNK_SIZE];

	size_t v_count;
	__int64 v_len;
	__int64 v_len2;
	__int64 v_offset;

again:
	FILE* stream_in;
	stream_in  = fopen( v_FileName_in, "rb" );   // use fopen, in favor of fopen_s
	if( stream_in == NULL )
	{
		printf("Unable to open input file %s\n\n", v_FileName_in);
		return;
	}

	v_len = _filelength(_fileno(stream_in));

	v_size = v_len > v_size ? v_size : v_len;

	v_offset = v_len-v_size;
	
	fsetpos(stream_in, &v_offset);
	printf("Starting at offset %lld\n\n", v_offset);

	while (v_size > 0)
	{
		if (v_size > CHUNK_SIZE)
			v_count = fread(v_buffer, sizeof(char), CHUNK_SIZE, stream_in);
		else
			v_count = fread(v_buffer, sizeof(char), v_size, stream_in);

		if (v_count != v_size)
		{
			printf("error reading file");
			return;
		}

		v_count = fwrite(v_buffer, 1, v_count, stdout);
		if (v_count != 0)
			v_size -= v_count;
		else
			v_size = 0;
	}
	fclose(stream_in);

	Sleep(5000);

    while(1)
	{
        stream_in  = fopen( v_FileName_in, "rb" );	
		if( stream_in == NULL )
		{
			printf("Unable to open input file %s\n\n", v_FileName_in);
			return;
		}

		//Get  the new length
		v_len2 = _filelength(_fileno(stream_in));

		if(v_len2 > v_len)
        {
			v_size =v_len2-v_len;
			v_offset =v_len2-v_size;

			//save new lehgth
            v_len=v_len2;

			fsetpos(stream_in, &v_offset);
			while (v_size > 0)
			{
				char* pTmp = NULL;
				if (v_size > CHUNK_SIZE)
				{
					v_count = fread(v_buffer,sizeof(char), CHUNK_SIZE, stream_in);
					if (v_count != CHUNK_SIZE)
					{
						printf("error reading file\n");
						return;
					}
					else
					{
						pTmp = new char[v_count + 1];
						pTmp[v_count] = '\0';
					}
                }
				else
				{
					v_count = fread(v_buffer, sizeof(char), (int)v_size, stream_in);				
					if (v_count != v_size)
					{
						printf("error reading file\n");
						return;
					}
					else {
						pTmp = new char[v_count + 1];
						pTmp[v_count] = '\0';
					}
				}				
                strncpy_s(pTmp, v_count + 1,v_buffer,v_count);
							
				printf("%s",pTmp);

				delete [] pTmp;
				pTmp=NULL;
						
				if (v_count > 0)
					v_size -= v_count;
				else
					v_size = 0;
			}
		}
		else if (v_len2 < v_len)
		{
			goto again;
		}

		Sleep(5000);
	}
	return;
}