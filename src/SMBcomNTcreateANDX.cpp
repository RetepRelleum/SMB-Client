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

#include <Debug.h>
#include <SMBcomNTcreateANDX.h>


uint32_t SMBcomNTcreateANDX::send(SMBcomTREEconnectANDX *smbComTREEconnectANDXiN,String fileNameIn,uint16_t rw){
        smbComTREEconnectANDX=smbComTREEconnectANDXiN;
        command=SMB_COM_NT_CREATE_ANDX;
        wordCount=0x18;
        fileName=fileNameIn;
        nameLength=fileName.length()+1;
        byteCount=nameLength;
        switch (rw) {
        case 0: desiredAccess=1;
                extFileAttributes=0;
                createDisposition =0x00000001;
                createOptions=0x00000000;
                break;
        case 1: desiredAccess=2;
                extFileAttributes=0;
                createOptions=0x00000000;
                break;
        case 2: desiredAccess=2;
                extFileAttributes=10;
                createOptions=0x00000001;
                break;
        }
        copyHeader(smbComTREEconnectANDX);
        length=getlength();
        debug_println("    ***************** SMBcomNTcreateANDX::send");
        Andx::send( );
        debug_println("    ***************** SMBcomNTcreateANDX::send");
        debug_println("    reserved");

        write( reserved);
        debug_println("    nameLength");
        write( nameLength);
        debug_println("    flags");
        write( flags);
        debug_println("    rootDirectoryFID");
        write( rootDirectoryFID);
        debug_println("    desiredAccess");
        write( desiredAccess);
        debug_println("    allocationSize");
        write( allocationSize);
        debug_println("    extFileAttributes");
        write( extFileAttributes);
        debug_println("    shareAccess");
        write( shareAccess);
        debug_println("    createDisposition");
        write( createDisposition);
        debug_println("    createOptions");
        write( createOptions);
        debug_println("    impersonationLevel");
        write( impersonationLevel);
        debug_println("    securityFlags");
        write( securityFlags);
        debug_println("    byteCount");
        write( byteCount);
        debug_println("    fileName");
        write(fileName);
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;
}

uint32_t SMBcomNTcreateANDX::receive(){
        debug_println("    ***************** SMBcomNTcreateANDX::receive");
        Andx::receive( );
        debug_println("    ***************** SMBcomNTcreateANDX::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    opLockLevel");
        opLockLevel=read8();
        debug_println("    fid");
        fid=read16();
        debug_println("    createDisposition");
        createDisposition =read32();
        debug_println("    createTime");
        createTime=read64();
        debug_println("    lastAccessTime");
        lastAccessTime=read64();
        debug_println("    lastWriteTime");
        lastWriteTime=read64();
        debug_println("    lastChangeTime");
        lastChangeTime=read64();
        debug_println("    extFileAttributes");
        extFileAttributes=read32();
        debug_println("    allocationSize");
        allocationSize=read64();
        debug_println("    endOfFile");
        endOfFile=read64();
        debug_println("    resourceType");
        resourceType=read16();
        debug_println("    nMPipeStatus");
        nMPipeStatus=read16();
        debug_println("    directory");
        directory=read8();
        debug_println("    byteCount");
        byteCount=read16();
        checkSize(  pos, length,  byteCount, wordCount);
        return status;

}
