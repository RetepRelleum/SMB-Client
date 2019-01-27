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

#ifndef SMBCOMREADANDX
#define SMBCOMREADANDX


#include <Andx.h>
#include <SMBcomNTcreateANDX.h>


class SMBcomREADandx : public Andx {


public:
  SMBcomREADandx(Client *clientIn){
          client =clientIn;
  };
  uint32_t send(SMBcomNTcreateANDX *smbComNTcreateANDX,uint8_t *dataIn,uint16_t sizeIn,uint16_t offsetIn);
  uint16_t getDataLength(){return dataLength;};
  protected:
uint16_t fid=0x0005;
uint32_t offset=0;
uint16_t maxCountOfBytesToReturn=0x0001;
uint16_t minCountOfBytesToReturn=0x0001;
uint32_t timeout=0x0000;
uint16_t remaining=0;
uint16_t offsetHigh=0;
uint16_t available=0;
uint16_t dataCompactionMode=0;
uint16_t reserved1=0;
uint16_t dataLength=0;
uint16_t dataOffset=0;
uint64_t reserved2;
uint16_t reserved3;
uint8_t *data;

uint32_t receive(uint8_t *data);
};

#endif
