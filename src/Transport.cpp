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
#include <Transport.h>

uint16_t Transport::getSize(){
        return 0;
}
uint16_t Transport::getlength(){
        return 0;
}
void Transport::send(){
        debug_println("    ***************** Transport::send");
        uint32_t s=0;
        ((uint8_t*)&s)[0]=((uint8_t*)&length)[3];
        ((uint8_t*)&s)[1]=((uint8_t*)&length)[2];
        ((uint8_t*)&s)[2]=((uint8_t*)&length)[1];
        ((uint8_t*)&s)[3]=((uint8_t*)&length)[0];
        write(s);


}
void Transport::receive(){
        debug_println("    ***************** Transport::read");
        debug_println("    length");
        uint32_t l=read32();
        ((uint8_t*)&length)[0]=((uint8_t*)&l)[3];
        ((uint8_t*)&length)[1]=((uint8_t*)&l)[2];
        ((uint8_t*)&length)[2]=((uint8_t*)&l)[1];
        ((uint8_t*)&length)[3]=((uint8_t*)&l)[0];
}
