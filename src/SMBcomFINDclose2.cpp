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
#include <SMBcomFINDclose2.h>


uint32_t SMBcomFINDclose2::send(TRANS2findFIRST2 *trans2find){
        command=SMB_COM_FIND_CLOSE2;
        wordCount=0x01;
        byteCount=0;
        searchHandle=trans2find->getSid();
        length=getlength();
        copyHeader(trans2find);
        debug_println("    ***************** SMBcomFINDclose2::send");
        Header::send( );
        debug_println("    ***************** SMBcomFINDclose2::send");
        debug_println("    byteCount");
        write(byteCount);
        debug_println("    searchHandle");
        write(searchHandle);
        debug_println("    dialectString");
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;
}

uint32_t SMBcomFINDclose2::receive(){
        Header::receive( );
        debug_println("    ***************** SMBcomFINDclose2::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    byteCount");
        byteCount=read16();
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        return status;

}
