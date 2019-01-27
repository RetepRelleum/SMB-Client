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
#include <SMBcomFLUSH.h>


uint32_t SMBcomFLUSH::send(SMBcomNTcreateANDX *smbComNTcreateANDX){
        command=SMB_COM_FLUSH;
        wordCount=0x01;
        byteCount=0;
        fid=smbComNTcreateANDX->getFid();
        copyHeader(smbComNTcreateANDX);
        length=getlength();
        debug_println("    ***************** SMBcomFLUSH::send");
        Header::send( );
        debug_println("    ***************** SMBcomFLUSH::send");
        debug_println("    fid");
        write( fid);
        debug_println("    byteCount");
        write(byteCount);
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;
}

uint32_t SMBcomFLUSH::receive(){
          debug_println("    ***************** SMBcomFLUSH::receive");
        Header::receive( );
        debug_println("    ***************** SMBcomFLUSH::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    byteCount");
        byteCount=read16();
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        return status;

}
