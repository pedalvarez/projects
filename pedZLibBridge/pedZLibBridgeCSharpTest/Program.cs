using System;
using System.Runtime.InteropServices;
using System.Text;

class Program
{	
    [DllImport("pedZLibBridge.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr Compress(IntPtr blob, long blobLen, long bufferSize, string compressionDict, out int resultLen);

    [DllImport("pedZLibBridge.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr Decompress(IntPtr blob, long blobLen, long bufferSize, string compressionDict, out int resultLen);

    static void Main(string[] args)
	{		
        String text = "ZLIB is a compression library compatible with the gzip format. It has been written by Jean-Loup Gailly and Mark Adler. It is free software.\r\nThe official page is there, but if you are interested only in Windows 95/98/NT/2000/XP/2003 support, you have found the right place.\r\nThere is also a page with a discussion list, Zlib-devel -- zlib compression library development discussions.\r\n\r\nThis page contains stuff built around zLib by Gilles Vollant, maker of WinImage and Smartversion.\r\nIt provides a DLL version of the library and pointers to other projects like MiniZip. It also intends to offer support for the DLL version and for assembly code optimisation.\r\n\r\nNEW: the source distribution of the zlib DLL is now merged with the standard zlib.";

        // make sure we have an UTF-8 from default
        byte[] utf8Bytes = System.Text.Encoding.UTF8.GetBytes(text);

        // Copy the array to unmanaged memory.
        int size = Marshal.SizeOf(utf8Bytes[0]) * utf8Bytes.Length;
        IntPtr pnt1 = Marshal.AllocHGlobal(size);
        Marshal.Copy(utf8Bytes, 0, pnt1, size);

        int len;
        IntPtr dataPtr = Compress(pnt1, size, 14668, "12345678900987654321",out len);
        Marshal.FreeHGlobal(pnt1);
        if (dataPtr == IntPtr.Zero)
        {
            // handle error
        }
        else
        {
            int len2;
            IntPtr dataPtr2 = Decompress(dataPtr, len, 14668, "12345678900987654321", out len2);

            byte[] data = new byte[len2];
            Marshal.Copy(dataPtr2, data, 0, len2);

            String result = System.Text.Encoding.UTF8.GetString(data, 0, len2);
        }
    }
}