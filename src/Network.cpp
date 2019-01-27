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
#include <Network.h>


byte Network::write(uint8_t data){
        #ifdef DEBUG
        debug(data);
        #endif
        pos++;
        return client->write(data);
}
byte Network::write(uint16_t data){
        byte ret=0;
        ret+=write(((uint8_t*)&data)[0]);
        ret+=write(((uint8_t*)&data)[1]);
        return ret;

}
byte Network::write(uint32_t data){
        byte ret=0;
        ret+=write(((uint8_t*)&data)[0]);
        ret+=write(((uint8_t*)&data)[1]);
        ret+=write(((uint8_t*)&data)[2]);
        ret+=write(((uint8_t*)&data)[3]);
        return ret;
}
byte Network::write(uint64_t data){
        byte ret=0;
        ret+=write(((uint8_t*)&data)[0]);
        ret+=write(((uint8_t*)&data)[1]);
        ret+=write(((uint8_t*)&data)[2]);
        ret+=write(((uint8_t*)&data)[3]);
        ret+=write(((uint8_t*)&data)[4]);
        ret+=write(((uint8_t*)&data)[5]);
        ret+=write(((uint8_t*)&data)[6]);
        ret+=write(((uint8_t*)&data)[7]);
        return ret;
}
byte Network::write(String data){
        byte ret=0;
        for (uint16_t i = 0; i < data.length(); i++) {
                ret+=write((uint8_t)data.charAt(i));
        }
        ret+=write((uint8_t)0x00);
        return ret;

}
byte Network::writeUnicode(String data){
        byte ret=0;
        for (uint16_t i = 0; i < data.length(); i++) {
                ret+=write((uint8_t)data.charAt(i));
                ret+=write((uint8_t)0x00);
        }
        ret+=write((uint8_t)0x00);
        ret+=write((uint8_t)0x00);
        return ret;
}

uint8_t Network::read8(){
        uint8_t data;
        uint32_t tstp=millis();
        while (!client->available()) {
                delay(10);
                if (millis()-tstp>1000) {
                        debug_println("Error get Data from SMB Server");
                        pos++;
                        return (uint8_t)0x00;
                }
        }

        data=client->read();
  #ifdef DEBUG
        debug(data);
  #endif
        pos++;
        return data;
}
uint16_t Network::read16(){
        uint16_t ret;
        ((uint8_t*)&ret)[0]=read8();
        ((uint8_t*)&ret)[1]=read8();
        debug_println(ret);
        return ret;
}
uint32_t Network::read32(){
        uint32_t ret;
        ((uint8_t*)&ret)[0]=read8();
        ((uint8_t*)&ret)[1]=read8();
        ((uint8_t*)&ret)[2]=read8();
        ((uint8_t*)&ret)[3]=read8();
        debug_println(ret);
        return ret;
}
uint64_t Network::read64(){
        uint64_t ret;
        ((uint8_t*)&ret)[0]=read8();
        ((uint8_t*)&ret)[1]=read8();
        ((uint8_t*)&ret)[2]=read8();
        ((uint8_t*)&ret)[3]=read8();
        ((uint8_t*)&ret)[5]=read8();
        ((uint8_t*)&ret)[6]=read8();
        ((uint8_t*)&ret)[7]=read8();
        ((uint8_t*)&ret)[8]=read8();
        uint32_t r1=ret/1000000000;
        uint32_t r2=(uint32_t)ret;
        debug_print(r1);
        debug_print(r2);
        return ret;
}
String Network::readUnicodeString(){
        String ret="";
        uint8_t read=read8();
        while(read!=0) {
                ret+=String((char)read);
                read8();
                read=read8();
        }
        read8();
        debug_println(ret);
        return ret;
}

String Network::readUnicodeString(uint8_t l){
        String ret="";
        for (uint8_t i = 0; i < l; i++) {
                ret+=String((char)read8());
        }
        debug_println(ret);
        return ret;
}
String Network::readOEMString(){
        String ret="";
        uint8_t read=read8();
        while(read!=0) {
                ret+=String((char)read);
                read=read8();
        }
        debug_println(ret);
        return ret;
}
uint16 Network::available(){
        return client->available();
}


void Network::debug(uint8_t data){
        if(pos%4==1) {
                debug_println(" ");
        }
        if (pos<100) { debug_print(" ");}
        if (pos<10) {debug_print(" ");}
        debug_print(pos);

        debug_print(" ");
        if (data<100) { debug_print(" ");}
        if (data<10) { debug_print(" ");}
        debug_print(data);
        debug_print(" 0X");
        if (data<16) { debug_print("0");}
        debug_print(data,HEX);
        debug_print(" ");
        for (size_t i = 0; i < 8-String(data,BIN).length(); i++) {
                debug_print("0");
        }
        debug_print(data,BIN);
        debug_print(" ");
        debug_println((char)data);

}
