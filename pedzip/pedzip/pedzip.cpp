// pedzip.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zlibengn.h"
#include <conio.h>
#include <stdio.h>

class MyZlibEngine : public ZlibEngine {
    public :
        void progress( int percent )
        {
            printf( "%3d%%\b\b\b\b", percent );
            if ( kbhit() ) {
                getch();
                m_AbortFlag = 1;
            }
        }
};

int main( int argc, char *argv[] )
{
    if ( argc < 2 ) {
        printf( "Usage: pedzip input-file\n"
                "\nCompresses input-file to test.zl\n"
                "\nDecompresses test.zl to test.out\n" );
        return 0;
    }
    MyZlibEngine *c_stream = new MyZlibEngine;
    printf( "\nHit any key to abort!\n\n" );
    printf( "Compressing %s to test.zl.  "
            "Percent complete: ", argv[ 1 ] );
    int result = c_stream->compress( argv[ 1 ], "test.zl",Z_DEFAULT_COMPRESSION );
    if ( result == Z_OK ) {
        printf( "\nDecompressing test.zl to test.out."
                "  Percent complete: " );
        result = c_stream->decompress( "test.zl", "test.out" );
        printf( "\n" );
    }
    if ( result != Z_OK )
        printf( "\nError! Result = %d\n", result );
    delete c_stream;
    return 1;
}