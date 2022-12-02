/* Copyright (C) 2008, 2009 Inge Eivind Henriksen
   See the file COPYING that comes with this distribution for copying permission.

   1. TM++, the "Software", is an embedded topic maps engine written in 
Standard C++. 

2. Copyright (C) 2007, 2008, 2009 Inge Eivind Henriksen. 

3. You are not allowed to use this software to make a database management
system without the written concent of Inge Eivind Henriksen.

4. If not violating any of the conditions of paragraph 3, then this
software is free software: you can redistribute it and/or modify it under
the terms of the MIT License as published by the Open Source Initiative.

5. This software is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the MIT License
for more details. 

6. You should have received a copy of the The MIT License
along with this software. If not, see <http://www.opensource.org/licenses>. 

The MIT License

Copyright (c) 2007, 2008, 2009 Inge Eivind Henriksen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*! \file
* \brief Contains the CBase64 class headers
*/
#include "base64Decoder.h"
#include <sstream>

/** Static Base64 character decoding lookup table */
const char Base64Decoder::decodeCharacterTable[256] = {
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
	,-1,62,-1,-1,-1,63,52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21
	,22,23,24,25,-1,-1,-1,-1,-1,-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
	,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1}; 

/*!
\brief Class constructor
*/
Base64Decoder::Base64Decoder()
{
}

/*!
\brief Class destructor
*/
Base64Decoder::~Base64Decoder()
{
}

/*!
\brief Decodes base 64 character data to binary data
\param in The character data to decode
\param out The decoded data
*/
void Base64Decoder::Decode(std::istringstream &in, std::ostream &out)
{
	char buff1[4];
	char buff2[4];
	unsigned int i=0, j;

	while(in.readsome(&buff2[i], 1) && buff2[i] != '=')
	{
		if (++i==4)
		{
			for (i=0;i!=4;i++)
				buff2[i] = decodeCharacterTable[buff2[i]];

			out << (char)((buff2[0] << 2) + ((buff2[1] & 0x30) >> 4));
			out << (char)(((buff2[1] & 0xf) << 4) + ((buff2[2] & 0x3c) >> 2));
			out << (char)(((buff2[2] & 0x3) << 6) + buff2[3]);

			i=0;
		}
	}

	if (i) 
	{
		for (j=i;j<4;j++) buff2[j] = '\0';
		for (j=0;j<4;j++) buff2[j] = decodeCharacterTable[buff2[j]];

		buff1[0] = (buff2[0] << 2) + ((buff2[1] & 0x30) >> 4);
		buff1[1] = ((buff2[1] & 0xf) << 4) + ((buff2[2] & 0x3c) >> 2);
		buff1[2] = ((buff2[2] & 0x3) << 6) + buff2[3];

		for (j=0;j<(i-1); j++) out << (char)buff1[j];
	}
}

