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

#ifndef SMBFFILE
#define SMBFFILE

#include <SMBcomNTcreateANDX.h>
#include <SMBcomWRITEandx.h>
#include <SMBcomREADandx.h>
#include <SMBcomCLOSE.h>
#include <SMBcomFLUSH.h>
#include <TRANS2findFIRST2.h>
#include <TRANS2findNEXT2.h>
#include <SMB.h>
class SMB;

class SMBFile : public SMBcomNTcreateANDX{

public:
  SMBFile(Client *clientIn):SMBcomNTcreateANDX(clientIn){
          client =clientIn;
  };
uint16_t  posi=0;
uint16_t  sid=0xFF;
bool isFile=false;
uint32_t resumeKey;
String fName;

SMB *smb;
SMBcomTREEconnectANDX *smbComTREEconnectANDX=NULL;
Client *client;
String name();
uint16_t available();
void close();
void flush();
char peek();
uint16_t position();
uint16_t print(char in);
uint16_t print(long in,uint8_t f=DEC);
uint16_t print(int in,uint8_t f=DEC);
uint16_t print(byte in,uint8_t f=DEC);
uint16_t print(double in, uint8_t decimalPlaces);
uint16_t print(String str);
uint16_t println(char in);
uint16_t println(long in,uint8_t f=DEC);
uint16_t println(int in,uint8_t f=DEC);
uint16_t println(byte in,uint8_t f=DEC);
uint16_t println(double in, uint8_t decimalPlaces);
uint16_t println(String str);
uint16_t println();
uint16_t seek(uint16_t posIn);
uint32_t size();
char read();
uint16_t read(uint8_t *buf, uint16_t len);
uint16_t write(char chr);
uint16_t write(byte byt);
uint16_t write(String str);
uint16_t write(uint8_t *buf, uint16_t len);
bool isDirectory();

SMBFile openNextFile();
void rewindDirectory();
operator bool();

};


#endif
