/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "ByteArrayInputStream.h"
#include <algorithm>

using namespace activemq::io;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
ByteArrayInputStream::ByteArrayInputStream(){
}

////////////////////////////////////////////////////////////////////////////////
ByteArrayInputStream::ByteArrayInputStream( const vector<unsigned char>& buffer ){
    setBuffer(buffer);
}

////////////////////////////////////////////////////////////////////////////////
ByteArrayInputStream::ByteArrayInputStream( const unsigned char* buffer,
                                            int bufferSize ){
    setByteArray( buffer, bufferSize );
}

////////////////////////////////////////////////////////////////////////////////
ByteArrayInputStream::~ByteArrayInputStream(){
}

////////////////////////////////////////////////////////////////////////////////
void ByteArrayInputStream::setBuffer( const vector<unsigned char>& buffer ){
    
    // We're using the default buffer.
    activeBuffer = &buffer;
   
    // Begin at the Beginning.
    reset();
}

////////////////////////////////////////////////////////////////////////////////
void ByteArrayInputStream::setByteArray( const unsigned char* lbuffer,
                                         int lbufferSize ){
    // We're using the default buffer.
    activeBuffer = &defaultBuffer;
    
    // Remove old data        
    defaultBuffer.clear();
   
    // Copy data to internal buffer.
    for( int ix = 0; ix < lbufferSize; ++ix )
    {
        defaultBuffer.push_back(lbuffer[ix]);
    }
   
    // Begin at the Beginning.
    reset();
}

////////////////////////////////////////////////////////////////////////////////
void ByteArrayInputStream::reset() throw (cms::CMSException){
    if( activeBuffer == NULL ){
        throw IOException( __FILE__, __LINE__, "Buffer has not been initialized" );
    }
    
    // Begin at the Beginning.
    pos = activeBuffer->begin();
}

////////////////////////////////////////////////////////////////////////////////
unsigned char ByteArrayInputStream::read() throw ( IOException ){
    if( pos == activeBuffer->end() ){
        throw IOException( __FILE__, __LINE__, "Buffer is empty" );    
    }
    
    return *(pos++);
}

////////////////////////////////////////////////////////////////////////////////
int ByteArrayInputStream::read( unsigned char* buffer, 
                                int bufferSize ) 
                                   throw ( IOException ){
    int ix = 0;
    
    for( ; ix < bufferSize; ++ix, ++pos)
    {
        if(pos == activeBuffer->end())
        {   
            // We don't have enough data to fulfill the request.
            throw IOException( __FILE__, __LINE__, "Reached the end of the buffer" );
        }
      
        buffer[ix] = *(pos);
    }
   
    return ix;
}
