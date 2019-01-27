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
#include <SMBcomWRITEandx.h>


uint32_t SMBcomWRITEandx::send(SMBcomNTcreateANDX *smbComNTcreateANDX,uint8_t *dataIn,uint16_t sizeIn,uint16_t offsetIn){
        command=SMB_COM_WRITE_ANDX;
        wordCount=0x0C;
        dataLength=sizeIn;
        offset=offsetIn;
        byteCount=sizeIn+1;
        data=dataIn;
        fid=smbComNTcreateANDX->getFid();
        copyHeader(smbComNTcreateANDX);
        length=getlength();
        debug_println("    ***************** SMBcomWRITEandx::send");
        Andx::send( );
        debug_println("    ***************** SMBcomWRITEandx::send");
        debug_println("    fid");
        write(fid);
        debug_println("    offset");
        write(offset);
        debug_println("    timeout");
        write(timeout);
        debug_println("    writeMode");
        write(writeMode);
        debug_println("    remaining");
        write(remaining);
        debug_println("    reserved");
        write( reserved);
        debug_println("    dataLength");
        write( dataLength);
        debug_println("    dataOffset");
        write( dataOffset);
        debug_println("    byteCount");
        write(byteCount);
        debug_println("    pad");
        write(pad);
        for (size_t i = 0; i < dataLength; i++) {
                write(data[i]);
        }

        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;
}

uint32_t SMBcomWRITEandx::receive(){
        debug_println("    ***************** SMBcomWRITEandx::receive");
        Andx::receive( );
        debug_println("    ***************** SMBcomWRITEandx::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    count");
        count=read16();
        debug_println("    available");
        available=read16();
        debug_println("    reserved");
        reserved=read16();
        debug_println("    reserved");
        reserved=read16();
        debug_println("    byteCount");
        byteCount=read16();
        checkSize(  pos, length,  byteCount, wordCount);
        return status;

}
