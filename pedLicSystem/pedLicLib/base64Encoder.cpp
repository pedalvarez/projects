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
#include "base64Encoder.h"
#include <sstream>

/** Static Base64 character encoding lookup table */
const char Base64Encoder::encodeCharacterTable[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*!
\brief Class constructor
*/
Base64Encoder::Base64Encoder()
{
}

/*!
\brief Class destructor
*/
Base64Encoder::~Base64Encoder()
{
}

/*!
\brief Encodes binary data to base 64 character data
\param in The data to encode
\param out The encoded data as characters
*/
void Base64Encoder::Encode(std::istream &in, std::ostringstream &out)
{
	char buff1[3];
	char buff2[4];
	unsigned int i=0, j;
	while(in.readsome(&buff1[i++], 1))
		if (i==3)
		{
			out << encodeCharacterTable[(buff1[0] & 0xfc) >> 2];
			out	<< encodeCharacterTable[((buff1[0] & 0x03) << 4) + ((buff1[1] & 0xf0) >> 4)];
			out	<< encodeCharacterTable[((buff1[1] & 0x0f) << 2) + ((buff1[2] & 0xc0) >> 6)];
			out	<< encodeCharacterTable[buff1[2] & 0x3f];
			i=0;
		}

	if (--i)
	{
		for(j=i;j<3;j++) buff1[j] = '\0';

		buff2[0] = (buff1[0] & 0xfc) >> 2;
		buff2[1] = ((buff1[0] & 0x03) << 4) + ((buff1[1] & 0xf0) >> 4);
		buff2[2] = ((buff1[1] & 0x0f) << 2) + ((buff1[2] & 0xc0) >> 6);
		buff2[3] = buff1[2] & 0x3f;

		for (j=0;j<(i+1);j++) out << encodeCharacterTable[buff2[j]];

		while(i++<3) out << '=';
	}

}
