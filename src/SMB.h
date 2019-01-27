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

#ifndef SMBDD
#define SMBDD
#include <Arduino.h>
#include <WiFi101.h>
#include <SMBFile.h>
#include <SMBcomTREEconnectANDX.h>
#include <SMBcomDELETEdirectory.h>
#define FILE_DIR 2

enum smbEnum:uint16_t {FILE_READ=0x00,FILE_WRITE=0x01};

class SMBFile;
class SMB :public SMBcomTREEconnectANDX{
        Client *client;
        SMBcomSESSIONsetupANDX smbComSESSIONsetupANDX;
public:
        SMB(Client *clientIn) : SMBcomTREEconnectANDX(clientIn),smbComSESSIONsetupANDX(clientIn){
                client=clientIn;
        };
        bool begin(String serverPathIn,String userIn,String passwordIn);
        bool exists(String filepath);
        bool mkdir(String filepath);
        SMBFile  open(String filepath, uint8_t mode=FILE_READ);
        bool remove(String filepath);
        bool rmdir( String filepath);
        bool loggOff( );
};

#endif
