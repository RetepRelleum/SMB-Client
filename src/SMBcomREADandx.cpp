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
#include <SMBcomREADandx.h>


uint32_t SMBcomREADandx::send(SMBcomNTcreateANDX *smbComNTcreateANDX,uint8_t *dataIn,uint16_t sizeIn,uint16_t offsetIn){
        command=SMB_COM_READ_ANDX;
        wordCount=0x0a;
        offset=offsetIn;
        byteCount=0;
        data=dataIn;
        fid=smbComNTcreateANDX->getFid();
        maxCountOfBytesToReturn=sizeIn;
        copyHeader(smbComNTcreateANDX);
        length=getlength();
        debug_println("    ***************** SMBcomREADandx::send");
        Andx::send( );
        debug_println("    ***************** SMBcomREADandx::send");

        debug_println("    fid");
        write(fid);
        debug_println("    offset");
        write(offset);
        debug_println("    maxCountOfBytesToReturn");
        write(maxCountOfBytesToReturn);
        debug_println("    minCountOfBytesToReturn");
        write(minCountOfBytesToReturn);
        debug_println("    timeout");
        write(timeout);
        debug_println("    remaining");
        write(remaining);

        debug_println("    byteCount");
        write(byteCount);

        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive(dataIn);
        return status;
}

uint32_t SMBcomREADandx::receive(uint8_t *data){
        debug_println("    ***************** SMBcomREADandx::receive");
        Andx::receive( );
        debug_println("    ***************** SMBcomREADandx::receive");
        if(status!=0) {
                return onError();
        }

        debug_println("    available");
        available=read16();
        debug_println("    dataCompactionMode");
        dataCompactionMode=read16();
        debug_println("    reserved1");
        reserved1=read16();
        debug_println("    dataLength");
        dataLength=read16();
        debug_println("    dataOffset");
        dataOffset=read16();
        debug_println("    reserved2");
        reserved2=read64();
        debug_println("    reserved3");
        reserved3=read16();
        debug_println("    byteCount");
        byteCount=read16();
        debug_println("    pad: ");
        while (pos<=(dataOffset+4)) {
                read8();
        }
        debug_println("    Data");
        for (uint i = 0; i < dataLength; i++) {
          data[i]=(char)read8();
        }

        checkSize(  pos, length,  byteCount, wordCount);

        return status;

}
