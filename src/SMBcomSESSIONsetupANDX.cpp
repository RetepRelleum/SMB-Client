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
#include <SMBcomSESSIONsetupANDX.h>


uint32_t SMBcomSESSIONsetupANDX::send(SMBcomNEGOTIATE *smbComNEGOTIATE){
       Serial.println((uint32_t)client);
        command=SMB_COM_SESSION_SETUP_ANDX;
        wordCount=0x0D;
        byteCount=oemPassword.length()+unicodePassword.length()+primaryDomain.length()+1+nativeOS.length()+1+nativeLanMan.length()+1+accountName.length()+1;
        copyHeader(smbComNEGOTIATE);
        sessionKey=smbComNEGOTIATE->getSessionKey();
        length=getlength();
        debug_println("    ***************** SMBcomSESSIONsetupANDX::send");
        Andx::send( );
        debug_println("    ***************** SMBcomSESSIONsetupANDX::send");
        debug_println("    maxBufferSize");
        write( maxBufferSize);
        debug_println("    maxMpxCount");
        write( maxMpxCount);
        debug_println("    vcNumber");
        write( vcNumber);
        debug_println("    sessionKey");
        write( sessionKey);
        debug_println("    OEMPasswordLen");
        write((uint16_t)( oemPassword.length()));
        debug_println("    UnicodePasswordLen");
        write( (uint16_t)(unicodePassword.length()*2));
        debug_println("    reserved");
        write( reserved);
        debug_println("    capabilities");
        write( capabilities);


        debug_println("    byteCount");
        write(byteCount);


        debug_println("    oemPassword");
        for (size_t i = 0; i < oemPassword.length(); i++) {
                write((uint8_t)oemPassword.charAt(i));
        }
        debug_println("    unicodePassword");
        for (size_t i = 0; i < unicodePassword.length(); i++) {
                write((uint8_t)unicodePassword.charAt(i));
                write((uint8_t)0);
        }

        debug_println("    accountName");
        write(accountName);
        debug_println("    primaryDomain");
        write(primaryDomain);
        debug_println("    nativeOS");
        write(nativeOS);
        debug_println("    nativeLanMan");
        write(nativeLanMan);
        checkSize(  pos, length,  byteCount, wordCount);
        pos=1;
        receive();
        return status;


}

uint32_t SMBcomSESSIONsetupANDX::receive(){
        Andx::receive( );
        debug_println("    ***************** SMBcomSESSIONsetupANDX::receive");
        if(status!=0) {
                return onError();
        }
        debug_println("    action");
        action=read16();
        debug_println("    byteCount");
        byteCount=read16();
        debug_println("    nativeOS");
        nativeOS=readOEMString();
        debug_println("    nativeLanMan");
        nativeLanMan=readOEMString();
        debug_println("    primaryDomain");
        primaryDomain=readOEMString();

        while (available()) {
          read8();
        }



        checkSize(  pos, length,  byteCount, wordCount);
        return status;

}
