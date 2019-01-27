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
#include <SMBcomTRANSACTION2.h>


void SMBcomTRANSACTION2::send(SMBcomTREEconnectANDX *smbComTREEconnectANDX){
        command=SMB_COM_TRANSACTION2;
        copyHeader(smbComTREEconnectANDX);
        debug_println("    ***************** SMBcomTRANSACTION2::send");
        Header::send( );
        debug_println("    ***************** SMBcomTRANSACTION2::send");
        debug_println("    totalParameterCount");
        write( totalParameterCount);
        debug_println("    totalDataCount");
        write( totalDataCount);
        debug_println("    maxParameterCount");
        write( maxParameterCount);
        debug_println("    maxDataCount");
        write( maxDataCount);
        debug_println("    maxSetupCount");
        write( maxSetupCount);
        debug_println("    reserved1");
        write( reserved1);
        debug_println("    flags");
        write( flags);
        debug_println("    timeout");
        write( timeout);
        debug_println("    reserved2");
        write( reserved2);
        debug_println("    parameterCount");
        write( parameterCount);
        debug_println("    parameterOffset");
        write( parameterOffset);
        debug_println("    dataCount");
        write( dataCount);
        debug_println("    dataOffset");
        write( dataOffset);
        debug_println("    setupCount");
        write( setupCount);
        debug_println("    reserved3");
        write( reserved3);
        debug_println("    setup");
        write( setup);
        debug_println("    byteCount");
        write( byteCount);
        debug_println("    name");
        write(name);
        debug_println("    pad");
        write((uint8_t)0);
        debug_println("    pad");
        write((uint8_t)0);
}

uint32_t SMBcomTRANSACTION2::receive(){
        Header::receive( );
        debug_println("    ***************** SMBcomTRANSACTION2::receive");
        if(status!=0) {
                return status;
        }
        debug_println("    totalParameterCount");
        totalParameterCount=read16();
        debug_println("    totalDataCount");
        totalDataCount=read16();
        debug_println("    reserved1");
        reserved1=read16();
        debug_println("    parameterCount");
        parameterCount=read16();
        debug_println("    parameterOffset");
        parameterOffset=read16();
        debug_println("    parameterDisplacement");
        parameterDisplacement=read16();
        debug_println("    dataCount");
        dataCount=read16();
        debug_println("    dataOffset");
        dataOffset=read16();
        debug_println("    dataDisplacement");
        dataDisplacement=read16();
        debug_println("    setupCount");
        setupCount=read8();
        debug_println("    reserved2");
        reserved2=read8();
        for (size_t i = 0; i < setupCount; i++) {
          debug_println("    setup");
          setup=read16();
        }
        debug_println("    byteCount");
        byteCount=read16();
        return status;

}

void SMBcomTRANSACTION2::readSMBinfoSTANDARD(){
        debug_println("    resumeKey");
        resumeKey=read32();
        debug_println("    creationDate");
        creationDate=read16();
        debug_println("    creationTime");
        creationTime=read16();
        debug_println("    lastAccessDate");
        lastAccessDate=read16();
        debug_println("    lastAccessTime");
        lastAccessTime=read16();
        debug_println("    lastWriteDate");
        lastWriteDate=read16();
        debug_println("    lastWriteTime");
        lastWriteTime=read16();
        debug_println("    fileDataSize");
        fileDataSize=read32();
        debug_println("    allocationSize");
        allocationSize=read32();
        debug_println("    attributes");
        attributes=read16();
        debug_println("    fileNameLength");
        fileNameLength=read8();
        debug_println("    fileName");
        fileName=readOEMString();

}
