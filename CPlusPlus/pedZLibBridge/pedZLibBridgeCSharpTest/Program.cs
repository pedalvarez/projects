﻿using System;
using System.Linq;
using System.Runtime.InteropServices;

class Program
{	
    [DllImport("pedZLibBridge.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr Compress(IntPtr blob, long blobLen, long bufferSize, IntPtr compressionDict, long dicLen, out int resultLen);

    [DllImport("pedZLibBridge.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr Decompress(IntPtr blob, long blobLen, long bufferSize, IntPtr compressionDict, long dicLen, out int resultLen);

    static void Main(string[] args)
	{
        String text = "ZLIB is a compression library compatible with the gzip format. It has been written by Jean-Loup Gailly and Mark Adler. It is free software.\r\nThe official page is there, but if you are interested only in Windows 95/98/NT/2000/XP/2003 support, you have found the right place.\r\nThere is also a page with a discussion list, Zlib-devel -- zlib compression library development discussions.\r\n\r\nThis page contains stuff built around zLib by Gilles Vollant, maker of WinImage and Smartversion.\r\nIt provides a DLL version of the library and pointers to other projects like MiniZip. It also intends to offer support for the DLL version and for assembly code optimisation.\r\n\r\nNEW: the source distribution of the zlib DLL is now merged with the standard zlib.";
               
        // make sure we have an UTF-8 from default
        byte[] utf8Bytes = System.Text.Encoding.UTF8.GetBytes(text);

        // Copy the array to unmanaged memory.
        int size = Marshal.SizeOf(utf8Bytes[0]) * utf8Bytes.Length;
        IntPtr pnt1 = Marshal.AllocHGlobal(size);
        Marshal.Copy(utf8Bytes, 0, pnt1, size);

        string dictionary = ZLibDictionary(text);

        //Dictionary
        byte[] utf8BytesDic = System.Text.Encoding.UTF8.GetBytes(dictionary);

        // Copy the array to unmanaged memory.
        int sizeDic = Marshal.SizeOf(utf8BytesDic[0]) * utf8BytesDic.Length;
        IntPtr pnt1Dic = Marshal.AllocHGlobal(sizeDic);
        Marshal.Copy(utf8BytesDic, 0, pnt1Dic, sizeDic);

        IntPtr dataPtr = Compress(pnt1, size, 14668, pnt1Dic, sizeDic, out int len);
        Marshal.FreeHGlobal(pnt1);
        if (dataPtr == IntPtr.Zero)
        {
            // handle error
        }
        else 
        {
            IntPtr dataPtr2 = Decompress(dataPtr, len, 14668, pnt1Dic, sizeDic, out int len2);
            byte[] data = new byte[len2];
            Marshal.Copy(dataPtr2, data, 0, len2);
            String result = System.Text.Encoding.UTF8.GetString(data, 0, len2);
            Console.Write(result);
        }
    }

    static string ZLibDictionary(string s)
    {
        const int ZLIB_MAX_DICT_SIZE = 32 * 1024;

        // From zlib manual https://www.zlib.net/manual.html
        // The dictionary should consist of strings(byte sequences) that are likely to be encountered later in the data to be compressed,
        // with the most commonly used strings preferably put towards the end of the dictionary.
        // Using a dictionary is most useful when the data to be compressed is short and can be predicted with good accuracy;
        // the data can then be compressed better than with the default empty dictionary.

        //\t tab
        //\n Line Feed
        //\r Carriage Return
        //\n\r Carriage Return + Line Feed
        //\v or \x0b Line Tabulation
        //\f or \x0c Form Feed
        //\x1c File Separator
        //\x1d Group Separator
        //\x1e Record Separator
        //\x85 Next Line(C1 Control Code)
        //\u2028	Line Separator
        //\u2029	Paragraph Separator

        var stringsarray = s.Split(new string[] { "\t", "\t\t", "\t\t\t", "\n", "\r", "\n\r", "\v", "\x0b", "\f", "\x0c", "\x1c", "x1d", "x1e", "\x85", "\u2028", "\u2029" }, StringSplitOptions.RemoveEmptyEntries);
        var common = stringsarray.ToList().GroupBy(e => e).Select(g => new { Value = g.Key, Count = g.Count() }).OrderByDescending(e => e.Count).Take(stringsarray.Length).Reverse().Select(v => v.Value); ;

        string result = string.Join("",common);
        if (result.Length > ZLIB_MAX_DICT_SIZE)
           return result[^ZLIB_MAX_DICT_SIZE..];
        else
           return result;
    }
}