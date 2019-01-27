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
#include <SMBcomTREEconnectANDX.h>


uint32_t SMBcomTREEconnectANDX::send(SMBcomSESSIONsetupANDX *smbComSESSIONsetupANDX,String pathIn,String passwordIn){
        command=SMB_COM_TREE_CONNECT_ANDX;
        wordCount=0x04;
        path=pathIn;
        password=passwordIn;
        byteCount=path.length()+1+service.length()+1+password.length()+1;
        copyHeader(smbComSESSIONsetupANDX);
        length=getlength();
        debug_println("    ***************** SMBcomTREEconnectANDX::send");
        Andx::send( );
        debug_println("    ***************** SMBcomTREEconnectANDX::send");
        debug_println("    flags");
        write( flags);
        debug_println("    PasswordLength");
        write( (uint16_t)(password.length()+1));
        debug_println("    byteCount");
        write(byteCount);
        debug_println("    password");
        write(password);
        debug_println("    Path");
        write(path);
        debug_println("    Service");
        write(service);
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;
}

uint32_t SMBcomTREEconnectANDX::receive(){
        debug_println("    ***************** SMBcomTREEconnectANDX::receive");
        Andx::receive( );
        debug_println("    ***************** SMBcomTREEconnectANDX::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    optionalSupport");
        optionalSupport=read16();
        debug_println("    byteCount");
        byteCount=read16();
        debug_println("    service");
        service=readOEMString();
        debug_println("    nativeFileSystem");
        nativeFileSystem=readOEMString();


        while (available()) {
                read8();
        }



        checkSize(  pos, length,  byteCount, wordCount);
        return status;

}
