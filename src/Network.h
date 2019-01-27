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

#ifndef NETWORK
#define NETWORK

#include <Arduino.h>
#include <WiFi101.h>
#include <SPI.h>



class Network {
protected:
        void debug(uint8_t data);
        Client *client;
        uint32_t length=100;
        uint8_t x;
        uint16_t pos=1;
        void begin(WiFiClient *clientIn);
        byte write(uint8_t data);
        byte write(uint16_t data);
        byte write(uint32_t data);
        byte write(uint64_t data);
        byte write(String data);
        byte writeUnicode(String data);
        uint8_t read8();
        uint16_t read16();
        uint32_t read32();
        uint64_t read64();
        String readUnicodeString();
        String readUnicodeString(uint8_t l);
        String readOEMString();
        uint16 available();

};

#endif
