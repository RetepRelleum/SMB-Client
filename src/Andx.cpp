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
#include <Andx.h>
void Andx::send(){
        debug_println("    ***************** Andx::send");
        Header::send( );
        debug_println("    ***************** Andx::send");
        debug_println("    andXCommand: ");
        write(andXCommand);
        debug_println("    andXReserved: ");
        write( andXReserved);
        debug_println("    andXOffset: ");
        write( andXOffset);
}

void Andx::receive(){
        Header::receive( );
        debug_println("    ***************** Andx::receive");
        debug_println("    andXCommand: ");
        andXCommand=read8();
        debug_println("    andXReserved: ");
        andXReserved=read8();
        debug_println("    andXOffset: ");
        andXOffset=read16();
}
