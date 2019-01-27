/* Copyright (c) 2019 Peter Müller
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated
* documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to
* whom the Software is furnished to do so, subject to the
* following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE
*
*/

#ifndef TRANS2FINDNEXT2
#define TRANS2FINDNEXT2

#include <SMBcomTRANSACTION2.h>
#include <SMBcomTREEconnectANDX.h>
#include <TRANS2findFIRST2.h>


class TRANS2findNEXT2 : public SMBcomTRANSACTION2 {
public:
  TRANS2findNEXT2(Client *clientIn){
          client =clientIn;
  };
  uint32_t send(SMBcomTREEconnectANDX *smbComTREEconnectANDX,uint16_t sidIn,String filenameIn,uint32_t resumeKeyIn);
  bool isEndOfSearch(){return endOfSearch;};
protected:
uint16_t sid=0;
uint16_t searchAttributes=0x0010;
uint16_t searchCount=1;
uint16_t flags=0x0014;
uint16_t informationLevel=0x001;
uint32_t searchStorageType=0;
uint16_t endOfSearch;
uint16_t eaErrorOffset;
uint16_t lastNameOffset;



uint32_t receive();
};

#endif
