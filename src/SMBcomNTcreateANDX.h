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

#ifndef SMBCOMNTCREATEANDX
#define SMBCOMNTCREATEANDX


#include <Andx.h>
#include <SMBcomTREEconnectANDX.h>



class SMBcomNTcreateANDX: public Andx {
public:
        SMBcomNTcreateANDX(Client *clientIn){
                client =clientIn;
        };
        uint32_t send(SMBcomTREEconnectANDX *smbComTREEconnectANDXiN,String fileNameIn,uint16_t rw);
        uint16_t getFid(){
                return fid;
        };
protected:
        SMBcomTREEconnectANDX *smbComTREEconnectANDX;
        uint8_t reserved=0;
        uint16_t nameLength=0;
        uint32_t flags=0;
        uint32_t rootDirectoryFID=0;
        uint32_t desiredAccess=0;
        uint64_t allocationSize=0;
        uint32_t extFileAttributes=0x00000010;
        uint32_t shareAccess=0x00000007;
        uint32_t createDisposition =0x00000003;
        uint32_t createOptions=0x00000001;
        uint32_t impersonationLevel=0x00000000;
        uint8_t securityFlags=0;
        String fileName="";
        uint8_t opLockLevel;
        uint16_t fid;
        uint64_t createTime;
        uint64_t lastAccessTime;
        uint64_t lastWriteTime;
        uint64_t lastChangeTime;
        uint64_t endOfFile;
        uint16_t resourceType;
        uint16_t nMPipeStatus;
        uint8_t directory;


        uint32_t receive();
};

#endif
