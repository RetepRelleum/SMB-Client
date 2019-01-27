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
#include <TRANS2findFIRST2.h>


uint32_t TRANS2findFIRST2::send(SMBcomTREEconnectANDX *smbComTREEconnectANDX,String fileNameIn){
        wordCount=0x0F;        //0x0E+0x01;
        fileName=fileNameIn;
        totalParameterCount=12+fileName.length()+1;
        byteCount=totalParameterCount+2+1;
        length=getlength();
        parameterCount=totalParameterCount;
        totalDataCount=0;
        dataCount=totalDataCount;
        setupCount=0x01;
        setup=0x0001;
        parameterOffset=68;
        debug_println("    ***************** TRANS2findFIRST2::send");
        SMBcomTRANSACTION2::send(smbComTREEconnectANDX);
        debug_println("    ***************** TRANS2findFIRST2::send");
        debug_println("    searchAttributes:");
        write(searchAttributes);
        debug_println("    searchCount:");
        write(searchCount);
        debug_println("    flags:");
        write(flags);
        debug_println("    informationLevel:");
        write(informationLevel);
        debug_println("    searchStorageType:");
        write(searchStorageType);
        debug_println("fileName:");
        write(fileName);
        checkSize(pos,length,byteCount,wordCount);
        pos=1;
        return receive();

}


uint32_t TRANS2findFIRST2::receive(){
        debug_println("***************** TRANS2findFIRST2::read");
        SMBcomTRANSACTION2::receive( );
        debug_println("***************** TRANS2findFIRST2::read");
        if (status!=0) return onError();

                debug_println("    pad: ");
        while (pos<=(parameterOffset+4)) {
                read8();
        }
        debug_println("    sid: ");
        sid=read16();
        debug_println("    searchCount: ");
        searchCount=read16();
        debug_println("    endOfSearch: ");
        endOfSearch=read16();
        debug_println("    eaErrorOffset: ");
        eaErrorOffset=read16();
        debug_println("    lastNameOffset: ");
        lastNameOffset=read16();
        debug_println("    pad: ");
        while (pos<=(dataOffset+4)) {
                read8();
        }
        readSMBinfoSTANDARD();
        checkSize(pos,length,byteCount,wordCount);
        pos=1;
        return status;
}
