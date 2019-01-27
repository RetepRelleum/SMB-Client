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

#ifndef SMBCOMNEGOTIATE
#define SMBCOMNEGOTIATE

#include <Header.h>
#include <WiFi101.h>



class SMBcomNEGOTIATE: public Header {
public:
        SMBcomNEGOTIATE(Client *clientIn){
                client =clientIn;
        };
        uint32_t send();
        uint32_t getSessionKey(){
                return sessionKey;
        };
protected:
        String dialectString[3]={" PCLAN1.0"," PC NETWORK PROGRAM 1.0"," NT LM 0.12"};
        size_t count= 3;
        uint16_t dialectIndex=0;
        uint8_t securityMode=0;
        uint16_t maxMpxCount=0;
        uint16_t maxNumberVcs=0;
        uint32_t maxBufferSize=0;
        uint32_t maxRawSize=0;
        uint32_t sessionKey=0;
        uint32_t capabilities=0;
        uint64_t systemTime=0;
        int16_t serverTimeZone=0;
        uint8_t challengeLength=0;
        uint8_t challenge[8];
        String domainName="";
        uint32_t receive();
};

#endif
