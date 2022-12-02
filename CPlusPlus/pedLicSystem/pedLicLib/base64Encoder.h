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

#pragma once

#include <sstream>


// 
/*! 
\ base on CBase64, only Encoder used here. STPEAL
\class CBase64
\brief Class handles RFC 4648 base 64 encoding and decoding 
\author Inge Eivind Henriksen
\date 2009
*/
class Base64Encoder
{
	private:
		static const char encodeCharacterTable[];		
	public:
		Base64Encoder();
		~Base64Encoder();
		void Encode(std::istream &in, std::ostringstream &out);		
};


