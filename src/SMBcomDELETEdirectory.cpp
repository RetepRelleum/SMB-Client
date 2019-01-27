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
#include <SMBcomDELETEdirectory.h>


uint32_t SMBcomDELETEdirectory::send(SMBcomTREEconnectANDX *smbComTREEconnectANDX,String fileNameIn){

        command=SMB_COM_DELETE_DIRECTORY;
        wordCount=0x00;
        byteCount=1+fileNameIn.length()+1;
        copyHeader(smbComTREEconnectANDX);
        length=getlength();
        debug_println("    ***************** SMBcomDELETEdirectory::send");
        Header::send( );
        debug_println("    ***************** SMBcomDELETEdirectory::send");

        debug_println("    byteCount");
        write(byteCount);
        debug_println("    bufferFormat");
        write(bufferFormat);
        debug_println("    fileNameIn");
        write(fileNameIn);

        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;
}

uint32_t SMBcomDELETEdirectory::receive(){
        debug_println("    ***************** SMBcomDELETEdirectory::receive");
        Header::receive( );
        debug_println("    ***************** SMBcomDELETEdirectory::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    byteCount");
        byteCount=read16();
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        return status;

}
