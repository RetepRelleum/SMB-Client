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

#ifndef WEBCLIENT
#define WEBCLIENT


#include "Client.h"


class WebClient: public Client  {

        int connect(IPAddress ip, uint16_t port) ;
        int connect(const char *host, uint16_t port) ;
        size_t write(uint8_t) ;
        size_t write(const uint8_t *buf, size_t size) ;
        int available() ;
        int read() ;
        int read(uint8_t *buf, size_t size) ;
        int peek() ;
        void flush() ;
        void stop() ;
        uint8_t connected() ;
        operator bool() ;

};

#endif
