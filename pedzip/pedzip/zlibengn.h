//
// This header file defines the ZlibEngine class used
// perform file compression and decompression using
// Zlib.
//

#if !defined( _ZLIBENGN_H )
#define _ZLIBENGN_H

//
// All of the Zlib code is compiled in C modules.  Fortunately,
// I can wrap the entire header in an 'extern "C"' declaration,
// and it will then link properly!
//

extern "C" {
#include "zlib/zlib.h"
}

#include <stdio.h>
#include <io.h>

class ZlibEngine : public z_stream {
    public :
        ZlibEngine();
        int compress( const char *input,
                      const char *output,
                      int level = 6 );
        int decompress( const char *input,
                        const char *output );
        void set_abort_flag( int i ){ m_AbortFlag = i; }
//
// These three functions are only used internally.
//
    protected :
        int percent();
        int load_input();
        int flush_output();
//
// Derived classes can provide versions of this
// virtual fns in order to customize their
// program's user interface.  The abort flag
// can be set by those functions.
//
    protected :
        virtual void progress( int percent ){};
        virtual void status( char *message ){};
        int m_AbortFlag;
//
// The remaining data members are used internally/
//
    protected :
        FILE *fin_;
        FILE *fout_;
        long length_;
        int err_;
        enum { input_length = 8 };
        unsigned char input_buffer_[ input_length ];
        enum { output_length = 8 };
        unsigned char output_buffer_[ output_length ];
};

//
// I define one error code in addition to those
// found in zlib.h
//
#define Z_USER_ABORT (-7)

#endif  // #if !defined( _ZLIBENGN_H )
