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
#include <Header.h>


void Header::send(){
        debug_println("    ***************** Header::send");
        Transport::send( );
        debug_println("    ***************** Header::send");
        write((uint8_t)0xFF);
        write((uint8_t)'S');
        write((uint8_t)'M');
        write((uint8_t)'B');
        debug_println("    command: ");
        write((uint8_t)command);
        debug_println("    status: ");
        write(status);
        debug_println("    flag: ");
        write(flag);
        debug_println("    flag2: ");
        write(flag2);
        debug_println("    pIDHigh: ");
        write(pIDHigh);
        debug_println("    key: ");
        write(key);
        debug_println("    cID: ");
        write(cID);
        debug_println("    SequenceNumber: ");
        write(sequenceNumber);
        debug_println("    reserved: ");
        write(reserved);
        debug_println("    tID: ");
        write(tID);
        debug_println("    pIDLow: ");
        write(pIDLow);
        debug_println("    uID: ");
        write(uID);
        debug_println("    mID: ");
        write(mID);
        debug_println("    wordCount: ");
        write(wordCount);
}

uint32_t Header::receive(){
        Transport::receive( );
        debug_println("    ***************** Header::receive");
        debug_println("    protocol: ");
        protocol=read32();
        debug_println("    Command: ");
        command=(commandEnum)read8();
        debug_println("    Status: ");
        status=read32();
        debug_println("    flag: ");
        flag=read8();
        debug_println("    flag2: ");
        flag2=read16();
        debug_println("    pIDHigh: ");
        pIDHigh=read16();
        debug_println("    Key: ");
        key=read32();
        debug_println("    cID: ");
        cID=read16();
        debug_println("    sequenceNumber: ");
        sequenceNumber=read16();
        debug_println("    reserved: ");
        reserved=read16();
        debug_println("    tID: ");
        tID=read16();
        debug_println("    pIDLow: ");
        pIDLow=read16();
        debug_println("    uID: ");
        uID=read16();
        debug_println("    mID: ");
        mID=read16();
        debug_println("    wordCount: ");
        wordCount=read8();
        return status;

}
void Header::checkSize( uint16_t pos,uint16_t length, uint16_t byteCount,uint8_t wordCount){
        debug_print("    pos: ");
        debug_println(pos-1);
        debug_print("    length: ");
        debug_println(length+4);
        debug_print("    byteCount: ");
        debug_println(byteCount);
        debug_print("    wordCount: ");
        debug_println(wordCount);
        debug_print("    byteCount: ");
        debug_println(byteCount+wordCount*2+32+7);
                debug_print("");
}



uint16_t Header::getSize(){
        return byteCount+wordCount*2+3;
}
uint16_t Header::getlength(){
        return Transport::getlength()+32+getSize();
}
void Header:: copyHeader(Header *header){
        uID=header->uID;
        tID=header->tID;
        mID=header->mID;
        pIDHigh=header->pIDHigh;
        pIDLow=header->pIDLow;
        cID=header->cID;
        key=header->key;
        sequenceNumber=header->sequenceNumber;
}

uint32_t Header::onError(){
        debug_println("    byteCount: ");
        byteCount=read16();
        checkSize(pos,length,byteCount,wordCount);
        pos=1;
        return status;
}
