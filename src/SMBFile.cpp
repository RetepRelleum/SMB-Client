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

#include <SMBFile.h>
#include <TRANS2findFIRST2.h>

String SMBFile::name(){
        return fileName;
}

uint16_t SMBFile::available(){
        uint16_t ret=endOfFile-posi;
        ret=posi<0 ? 0 : ret;
        return ret;
}
char SMBFile::read(){
        uint8_t a[1]={'a'};
        read(a,(uint16_t)1);
        return a[0];
}
uint16_t SMBFile::read(uint8_t *buf, uint16_t len){
        SMBcomREADandx smbComREADandx(client);
        uint32_t ret;
        ret=smbComREADandx.send(this,buf,len,posi);
        if (ret) {
                Serial.print("SMB Error smbComREADandx: ");
                Serial.println(ret,HEX);
        }
        posi+=smbComREADandx.getDataLength();
        return smbComREADandx.getDataLength();
}

void SMBFile::close(){
        SMBcomCLOSE smbComClose(client);
        smbComClose.send(this,WiFi.getTime()+60*60);

}

uint16_t SMBFile::position(){
        return posi;
}


uint16_t SMBFile::write(uint8_t *buf, uint16_t len){
        SMBcomWRITEandx smbComWRITEandx(client);
        uint32_t ret;
        ret=smbComWRITEandx.send(this,buf,len,posi);
        if (ret) {
                Serial.print("SMB Error smbComWRITEandx: ");
                Serial.println(ret,HEX);
        }
        posi+=smbComWRITEandx.getCount();
        return smbComWRITEandx.getCount();
}

uint16_t SMBFile::write(char chr){
        uint8_t c[1];
        c[0]=(uint8_t)chr;
        return write(c,1);
}
uint16_t SMBFile::write(byte byt){
        uint8_t c[1];
        c[0]=(uint8_t)byt;
        return write(c,1);
}

uint16_t SMBFile::write(String str){
        return write((uint8_t*)str.c_str(),str.length());
}


void SMBFile::flush(){
        SMBcomFLUSH smbComFlush(client);
        smbComFlush.send(this);
}
char SMBFile::peek(){
        uint8_t ret=read();
        posi--;
        return ret;
}
uint16_t SMBFile::print(char in){
        return print(String(in));

}
uint16_t SMBFile::print(long in,uint8_t f){
        return print(String(in,f));

}

uint16_t SMBFile::print(int in,uint8_t f){
        return print(String(in,f));

}
uint16_t SMBFile::print(byte in,uint8_t f){
        return print(String(in,f));

}
uint16_t SMBFile::print(double in, uint8_t decimalPlaces){
        return print(String(in,decimalPlaces));
}

uint16_t SMBFile::print(String str){
        return write((uint8_t*)str.c_str(),str.length());
}
uint16_t SMBFile::println(char in){
        return println(String(in));

}
uint16_t SMBFile::println(long in,uint8_t f){
        return println(String(in,f));

}

uint16_t SMBFile::println(int in,uint8_t f){
        return println(String(in,f));

}
uint16_t SMBFile::println(byte in,uint8_t f){
        return println(String(in,f));

}
uint16_t SMBFile::println(double in, uint8_t decimalPlaces){
        return println(String(in,decimalPlaces));
}
uint16_t SMBFile::println(){
        String str="";
        str+="\r\n";
        return write((uint8_t*)str.c_str(),str.length());
}

uint16_t SMBFile::println(String str){
        str+="\r\n";
        return write((uint8_t*)str.c_str(),str.length());
}

uint16_t SMBFile::seek(uint16_t posIn){
        posi=posIn;
        return true;
}

bool SMBFile::isDirectory(){

        return directory;
}

SMBFile SMBFile::openNextFile(){

  TRANS2findFIRST2 trans2findFIRST2(client);
        uint32_t ret;
        if (isDirectory()) {
                Serial.println("dir");
                if(sid==0xFF) {
                        fName=name()+"\\*";
                        ret=trans2findFIRST2.send(smbComTREEconnectANDX,fName);
                        if (ret) {
                                Serial.print("SMB Error trans2findFIRST2: ");
                                Serial.println(ret,HEX);
                                SMBFile sm(client);
                                return sm;
                        }
                        sid=trans2findFIRST2.getSid();
                        fName=trans2findFIRST2.getFileName();
                        resumeKey=trans2findFIRST2.getResumeKey();

                        if (!fName.equalsIgnoreCase(".")) {
                                return smb->open(fName,FILE_READ);

                        }else if (trans2findFIRST2.isEndOfSearch()) {
                                Serial.println("endOfSearch");
                                SMBFile smbFile1(client);
                                return smbFile1;
                        }
                        else{
                                return openNextFile();
                        }
                }
                TRANS2findNEXT2 trans2findNEXT2(client);
                ret=trans2findNEXT2.send(smbComTREEconnectANDX,sid,fName,resumeKey);
                if (ret) {
                        Serial.print("SMB Error trans2findNEXT2: ");
                        Serial.println(ret,HEX);
                }
                fName=trans2findNEXT2.getFileName();
                resumeKey=trans2findNEXT2.getResumeKey();
                if (fName.equalsIgnoreCase(".") ||fName.equalsIgnoreCase("..") ) {
                        return openNextFile();
                }else if (trans2findNEXT2.isEndOfSearch()) {
                        Serial.println("endOfSearch");
                        SMBFile smbFile2(client);
                        return smbFile2;
                }else{
                        return smb->open(fName,FILE_READ);
                }
        }
        SMBFile smbFile(client);
        return smbFile;

}

SMBFile::operator bool() {
        return isFile;
}

uint32_t SMBFile::size(){
        return allocationSize;
}
void SMBFile::rewindDirectory(){
        sid=0xFF;
}
