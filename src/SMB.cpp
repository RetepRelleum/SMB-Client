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
#include <SMB.h>
#include <SMBcomNEGOTIATE.h>
#include <SMBcomFINDclose2.h>
#include <SMBcomLOGOFFandx.h>
#include <SMBcomDELETE.h>
#include <SMBcomDELETEdirectory.h>



bool SMB::begin(String serverPathIn,String userIn,String passwordIn){
        if(!client->connected()) {
                String server=serverPathIn;
                server.replace("\\\\", "");
                server.remove(server.indexOf("\\"));
                Serial.println(server);
                if (client->connect(server.c_str(),445)) {
                        Serial.println("connected");
                }
        }
        SMBcomNEGOTIATE smbComNEGOTIATE(client);
        smbComNEGOTIATE.send();
        if (smbComNEGOTIATE.getStatus()) {
                Serial.print("Error smbComNEGOTIATE: 0x");
                Serial.print(smbComNEGOTIATE.getStatus(),HEX);
                return false;
        }
     Serial.println((uint32_t)client);
        smbComSESSIONsetupANDX.send(&smbComNEGOTIATE);
        if (smbComSESSIONsetupANDX.getStatus()) {
                Serial.print("Error smbComSESSIONsetupANDX: 0x");
                Serial.print(smbComSESSIONsetupANDX.getStatus(),HEX);
                return false;
        }

        send(&smbComSESSIONsetupANDX,serverPathIn,passwordIn);
        if (getStatus()) {
                Serial.print("Error smbComTREEconnectANDX: 0x");
                Serial.print(getStatus(),HEX);
                return false;
        }
        return true;
}

bool SMB::exists(String filepath){
        TRANS2findFIRST2 trans2findFIRST2(client);
        trans2findFIRST2.send(this,filepath);
        if (trans2findFIRST2.getStatus()) {
                if(trans2findFIRST2.getStatus()!=0x20001) {
                        Serial.print("Error trans2findFIRST2: 0x");
                        Serial.print(trans2findFIRST2.getStatus(),HEX);
                }
                return false;
        }
        SMBcomFINDclose2 smbComFINDclose2(client);
        smbComFINDclose2.send(&trans2findFIRST2);
        if (smbComFINDclose2.getStatus()) {
                Serial.print("Error smbComFINDclose2: 0x");
                Serial.print(smbComFINDclose2.getStatus(),HEX);
                return false;
        }
        return true;
}

bool SMB::mkdir(String filepath){
        SMBcomNTcreateANDX smbComNTcreateANDX(client);
        smbComNTcreateANDX.send(this,filepath,FILE_DIR);
        if (smbComNTcreateANDX.getStatus()) {
                Serial.print("Error smbComNTcreateANDX: 0x");
                Serial.print(smbComNTcreateANDX.getStatus(),HEX);
                return false;
        }
        SMBcomCLOSE smbComCLOSE(client);
        smbComCLOSE.send(&smbComNTcreateANDX,WiFi.getTime());
        if (smbComCLOSE.getStatus()) {
                Serial.print("Error smbComCLOSE: 0x");
                Serial.print(smbComCLOSE.getStatus(),HEX);
                return false;
        }
        return true;
}
SMBFile SMB::open(String filepath, uint8_t mode){
        SMBFile smbFile(client);
        smbFile.send(this,filepath,mode);
        if (smbFile.getStatus()) {
                Serial.print("Error smbFile: 0x");
                Serial.print(smbFile.getStatus(),HEX);
                return smbFile;
        }
        smbFile.smbComTREEconnectANDX=this;
        smbFile.smb=this;
        smbFile.isFile=true;
        return smbFile;
}

bool SMB::loggOff( ){
        SMBcomLOGOFFandx smbComLOGOFFandx(client);
        smbComLOGOFFandx.send(&smbComSESSIONsetupANDX);
        if (smbComLOGOFFandx.getStatus()) {
                Serial.print("Error smbComLOGOFFandx: 0x");
                Serial.print(smbComLOGOFFandx.getStatus(),HEX);
                return false;
        }
        return true;
}

bool SMB::remove(String filepath){
        SMBcomDELETE smbComDELETE(client);
        smbComDELETE.send(this,filepath);
        if (smbComDELETE.getStatus()) {
                Serial.print("Error smbComDELETE: 0x");
                Serial.print(smbComDELETE.getStatus(),HEX);
                return false;
        }
        return true;
}



bool SMB::rmdir(String filepath){
        SMBcomDELETEdirectory smbComDELETEdirectory(client);
        smbComDELETEdirectory.send(this,filepath);
        if (smbComDELETEdirectory.getStatus()) {
                Serial.print("Error smbComDELETEdirectory: 0x");
                Serial.print(smbComDELETEdirectory.getStatus(),HEX);
                return false;
        }
        return true;

}
