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

#ifndef ACTIVEMQ_EXCEPTIONS_ACTIVEMQEXCEPTIONTEST_H_
#define ACTIVEMQ_EXCEPTIONS_ACTIVEMQEXCEPTIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <activemq/exceptions/ActiveMQException.h>
#include <string.h>

namespace activemq{
namespace exceptions{

    class ActiveMQExceptionTest : public CppUnit::TestFixture {

      CPPUNIT_TEST_SUITE( ActiveMQExceptionTest );
      CPPUNIT_TEST( testMessage0 );
      CPPUNIT_TEST( testMessage3 );
      CPPUNIT_TEST( testMacros );
      CPPUNIT_TEST_SUITE_END();

    public:

        virtual ~ActiveMQExceptionTest(){}

        virtual void setUp(){}
        virtual void tearDown(){}

        void testMacros();
        void testMessage0();
        void testMessage3();

    };

}}

#endif /*ACTIVEMQ_EXCEPTIONS_ACTIVEMQEXCEPTIONTEST_H_*/
