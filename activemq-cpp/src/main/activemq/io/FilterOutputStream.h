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

#ifndef _ACTIVEMQ_IO_FILTEROUTPUTSTREAM_H_
#define _ACTIVEMQ_IO_FILTEROUTPUTSTREAM_H_

#include <activemq/io/OutputStream.h>
#include <activemq/io/IOException.h>
#include <activemq/concurrent/Mutex.h>

namespace activemq{
namespace io{

    /**
     * This class is the superclass of all classes that filter output 
     * streams. These streams sit on top of an already existing output 
     * stream (the underlying output stream) which it uses as its basic 
     * sink of data, but possibly transforming the data along the way or 
     * providing additional functionality.
     * 
     * The class FilterOutputStream itself simply overrides all methods of 
     * OutputStream with versions that pass all requests to the underlying 
     * output stream. Subclasses of FilterOutputStream may further override 
     * some of these methods as well as provide additional methods and 
     * fields.
     * 
     * Due to the lack of garbage collection in C++ a design decision was 
     * made to add a boolean parameter to the constructor indicating if the
     * wrapped <code>InputStream</code> is owned by this object.  That way
     * creation of the underlying stream can occur in a Java like way. Ex:
     * 
     *  DataOutputStream os = new DataOutputStream( new OutputStream(), true )
     */
    class FilterOutputStream : public OutputStream
    {
    protected:
    
        // The output Stream to wrap
        OutputStream* outputStream;
        
        // Synchronization object.
        concurrent::Mutex mutex;
        
        // Indicates if we own the wrapped stream
        bool own;

    public:

        /**
         * Constructor, creates a wrapped output stream
         * @param outputStream the OutputStream to wrap
         */
    	FilterOutputStream( OutputStream* outputStream, bool own = false ){
            this->outputStream = outputStream;
            this->own = own;
        }
        
    	virtual ~FilterOutputStream() {
            try {
                if( own == true ) delete outputStream;
            }
            AMQ_CATCH_NOTHROW( IOException )
            AMQ_CATCHALL_NOTHROW( )                 
        }

        /**
         * Writes a single byte to the output stream.  The write method of 
         * FilterOutputStream calls the write method of its underlying output 
         * stream, that is, it performs out.write(b).
         * @param c the byte.
         * @throws IOException thrown if an error occurs.
         */
        virtual void write( unsigned char c ) throw ( IOException ) {
            try {
                outputStream->write( c );
            }
            AMQ_CATCH_RETHROW( IOException )
            AMQ_CATCHALL_THROW( IOException )
        }
        
        /**
         * Writes an array of bytes to the output stream.  The write method of 
         * FilterOutputStream calls the write method of one argument on each 
         * byte to output.
         * @param buffer The array of bytes to write.
         * @param len The number of bytes from the buffer to be written.
         * @throws IOException thrown if an error occurs.
         */
        virtual void write( const unsigned char* buffer, int len ) throw ( IOException ) {
            try {
                for( int ix = 0; ix < len; ++ix )
                {
                    outputStream->write( buffer[ix] );
                }
            }
            AMQ_CATCH_RETHROW( IOException )
            AMQ_CATCHALL_THROW( IOException )
        }
        
        /**
         * Flushes any pending writes in this output stream.
         * The flush method of FilterOutputStream calls the flush method 
         * of its underlying output stream
         * @throws IOException
         */
        virtual void flush() throw ( IOException ) {
            try {
                outputStream->flush();
            }
            AMQ_CATCH_RETHROW( IOException )
            AMQ_CATCHALL_THROW( IOException )
        }
        
        /**
         * Close the Stream, the FilterOutputStream simply calls the close
         * method of the underlying stream
         * @throws CMSException
         */
        virtual void close() throw ( cms::CMSException ) {
            try {
                outputStream->close();
            }
            AMQ_CATCH_RETHROW( IOException )
            AMQ_CATCHALL_THROW( IOException )
        }

    public:  // Synchronizable
    
        /**
         * Waits on a signal from this object, which is generated
         * by a call to Notify.  Must have this object locked before
         * calling.
         * @throws ActiveMQException
         */
        virtual void lock() throw( exceptions::ActiveMQException ){
            mutex.lock();
        }
    
        /**
         * Unlocks the object.
         * @throws ActiveMQException
         */
        virtual void unlock() throw( exceptions::ActiveMQException ){ 
            mutex.unlock();
        }
        
        /**
         * Waits on a signal from this object, which is generated
         * by a call to Notify.  Must have this object locked before
         * calling.
         * @throws ActiveMQException
         */
        virtual void wait() throw( exceptions::ActiveMQException ){
            mutex.wait();
        }
    
        /**
         * Waits on a signal from this object, which is generated
         * by a call to Notify.  Must have this object locked before
         * calling.  This wait will timeout after the specified time
         * interval.
         * @param millisecs the time in millisecsonds to wait, or WAIT_INIFINITE
         * @throws ActiveMQException
         */
        virtual void wait( unsigned long millisecs ) throw( exceptions::ActiveMQException ){
            mutex.wait(millisecs);
        }

        /**
         * Signals a waiter on this object that it can now wake
         * up and continue.  Must have this object locked before
         * calling.
         * @throws ActiveMQException
         */
        virtual void notify() throw( exceptions::ActiveMQException ){
            mutex.notify();
        }
        
        /**
         * Signals the waiters on this object that it can now wake
         * up and continue.  Must have this object locked before
         * calling.
         * @throws ActiveMQException
         */
        virtual void notifyAll() throw( exceptions::ActiveMQException ){
            mutex.notifyAll();
        }

    };

}}

#endif /*_ACTIVEMQ_IO_FILTEROUTPUTSTREAM_H_*/
