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

#ifndef SMBCOMTRANSACTION2
#define SMBCOMTRANSACTION2


#include <Header.h>
#include <SMBcomTREEconnectANDX.h>


class SMBcomTRANSACTION2: public Header {
public:
        void send(SMBcomTREEconnectANDX *smbComTREEconnectANDX);
        String getFileName(){
                return fileName;
        };
        uint32_t getResumeKey(){
                return resumeKey;
        };
protected:
        String nativeOS="";
        uint16_t totalParameterCount=16;
        uint16_t totalDataCount=0;
        uint16_t maxParameterCount=200;
        uint16_t maxDataCount=200;
        uint8_t maxSetupCount=200;
        uint8_t reserved1=0;
        uint16_t flags=0;
        uint32_t timeout=250;
        uint16_t reserved2=0;
        uint16_t parameterCount=1;
        uint16_t parameterOffset=66;
        uint16_t dataCount=0;
        uint16_t dataOffset=0;
        uint8_t setupCount=1;
        uint8_t reserved3=0;
        uint16_t setup=1;//??
        uint8_t name=0;
        uint16_t pad1=0;

        uint16_t parameterDisplacement=0;
        uint16_t dataDisplacement=0;

        uint32_t resumeKey=0;
        uint16_t creationDate;
        uint16_t creationTime;
        uint16_t lastAccessDate;
        uint16_t lastAccessTime;
        uint16_t lastWriteDate;
        uint16_t lastWriteTime;
        uint32_t fileDataSize;
        uint32_t allocationSize;
        uint16_t attributes;
        uint8_t fileNameLength;
        String fileName;


        uint32_t receive();
        void readSMBinfoSTANDARD();





};

#endif
