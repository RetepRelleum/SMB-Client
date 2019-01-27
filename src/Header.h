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
#ifndef HEADER
#define HEADER


#include <Transport.h>

enum commandEnum:uint8_t {SMB_COM_DELETE_DIRECTORY=0x01,
                          SMB_COM_CLOSE=0x04,
                          SMB_COM_FLUSH=0x05,
                          SMB_COM_DELETE=0X06,
                          SMB_COM_OPEN_ANDX=0x2D,
                          SMB_COM_READ_ANDX=0x2E,
                          SMB_COM_WRITE_ANDX=0x2F,
                          SMB_COM_TRANSACTION2=0x32,
                          SMB_COM_FIND_CLOSE2=0x34,
                          SMB_COM_NEGOTIATE=0x72,
                          SMB_COM_SESSION_SETUP_ANDX=0x73,
                          SMB_COM_LOGOFF_ANDX=0x74,
                          SMB_COM_TREE_CONNECT_ANDX=0x75,
                          SMB_COM_NT_CREATE_ANDX=0xA2};

class Header : public Transport {
public:
uint32_t  getStatus(){return status;};
protected:
uint32_t protocol =0;
uint32_t status=0;
uint8_t flag=0x18;
/*SMB Flags2 contains 0xC843
   1... .... .... .... = Unicode Strings: Strings are Unicode
   .1.. .... .... .... = Error Code Type: Error codes are NT error codes
   ..0. .... .... .... = Execute-Only Reads: Do not permit reads if execute-only
   ...0 .... .... .... = Dfs: Do not resolve pathnames with Dfs
   .... 1... .... .... = Extended security negotiation is supported
   .... .... .1.. .... = Long Names Used
   .... .... .... .0.. = Security signatures are not supported
   .... .... .... ..1. = Extended Attributes: Extended attributes are supported
   .... .... .... ...1 = Long Names Allowed
   1100 1000 0100 0001
 */
uint16_t flag2=0x0041;
commandEnum command=SMB_COM_NEGOTIATE;
uint16_t pIDHigh=0;
uint32_t key=0;
uint16_t cID=0;
uint16_t sequenceNumber=0;
uint16_t reserved=0;
uint16_t tID=0;
uint16_t pIDLow=0;
uint16_t uID=0;
uint16_t mID=0;
uint8_t wordCount=1;
uint16_t byteCount=0;
uint16_t getSize();
uint16_t getlength();
void send();
uint32_t receive();
void checkSize( uint16_t pos,uint16_t length, uint16_t byteCount,uint8_t wordCount);
void copyHeader(Header *header);
uint32_t onError();
};

#endif
