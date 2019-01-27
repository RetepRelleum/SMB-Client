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

#ifndef SMBCOMSESSIONSETUPANDX
#define SMBCOMSESSIONSETUPANDX


#include <Andx.h>
#include <SMBcomNEGOTIATE.h>


class SMBcomSESSIONsetupANDX: public Andx {
public:
        SMBcomSESSIONsetupANDX(Client *clientIn){
                client =clientIn;
        };
        uint32_t  send( SMBcomNEGOTIATE *smbComTREEconnectANDX);
protected:
        uint16_t maxBufferSize=300;
        uint16_t maxMpxCount=0x10;
        uint16_t vcNumber=0x0000;
        uint32_t sessionKey=0;
        uint32_t reserved=0x00;
        uint32_t capabilities=0x00000005;
        uint16_t action=0;
        String oemPassword="";
        String unicodePassword="";
        String accountName="";
        String primaryDomain="";
        String nativeOS="Windows 4.0";
        String nativeLanMan="Windows 4.0";
        uint32_t receive();
};

#endif
