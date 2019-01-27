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
#include <SMBcomNEGOTIATE.h>


uint32_t SMBcomNEGOTIATE::send(){
        command=SMB_COM_NEGOTIATE;
        wordCount=0x00;
        uint8_t l=0;
        for (size_t i = 0; i < count; i++) {
                l+=dialectString[i].length()+1;
        }
        byteCount=l;
        length=getlength();
        debug_println("    ***************** SMBcomNEGOTIATE::send");
        Header::send( );
        debug_println("    ***************** SMBcomNEGOTIATE::send");
        debug_println("    byteCount");
        write(byteCount);
        debug_println("    dialectString");
        for (size_t i = 0; i < count; i++) {
                write(dialectString[i]);
        }
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;
}

uint32_t SMBcomNEGOTIATE::receive(){
        Header::receive( );
        debug_println("    ***************** SMBcomNEGOTIATE::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    dialectIndex");
        dialectIndex=read16();
        debug_println("    securityMode");
        securityMode=read8();
        debug_println("    maxMpxCount");
        maxMpxCount=read16();
        debug_println("    maxNumberVcs");
        maxNumberVcs=read16();
        debug_println("    maxBufferSize");
        maxBufferSize=read32();
        debug_println("    maxRawSize");
        maxRawSize=read32();
        debug_println("    sessionKey");
        sessionKey=read32();
        debug_println("    capabilities");
        capabilities=read32();
        debug_println("    systemTime");
        systemTime=read64();
        debug_println("    serverTimeZone");
        serverTimeZone=read16();
        debug_println("    challengeLength");
        challengeLength=read8();
        debug_println("    byteCount");
        byteCount=read16();
        debug_println("    challenge");
        challenge[0]=read8();
        challenge[1]=read8();
        challenge[2]=read8();
        challenge[3]=read8();
        challenge[4]=read8();
        challenge[5]=read8();
        challenge[6]=read8();
        challenge[7]=read8();
        debug_println("    domainName");
        domainName=readUnicodeString();
        checkSize(  pos, length,  byteCount, wordCount);
        return status;
}
