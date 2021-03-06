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

#include "StringBufferTest.h"

#include <decaf/lang/String.h>
#include <decaf/lang/StringBuffer.h>
#include <decaf/lang/StringBuilder.h>
#include <decaf/lang/Short.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/Float.h>
#include <decaf/lang/Double.h>
#include <decaf/lang/Pointer.h>
#include <decaf/lang/exceptions/IndexOutOfBoundsException.h>
#include <decaf/lang/exceptions/NegativeArraySizeException.h>
#include <decaf/lang/exceptions/NullPointerException.h>
#include <decaf/lang/exceptions/StringIndexOutOfBoundsException.h>
#include <decaf/util/Arrays.h>

using namespace std;
using namespace decaf;
using namespace decaf::util;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;

////////////////////////////////////////////////////////////////////////////////
StringBufferTest::StringBufferTest() {
}

////////////////////////////////////////////////////////////////////////////////
StringBufferTest::~StringBufferTest() {
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testDefaultConstructor() {
    StringBuffer builder;
    CPPUNIT_ASSERT_EQUAL(16, builder.capacity());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testConstructorInt() {

    StringBuffer sb(24);
    CPPUNIT_ASSERT_EQUAL(24, sb.capacity());

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a NegativeArraySizeException",
        StringBuffer(-1),
        NegativeArraySizeException);

    CPPUNIT_ASSERT_NO_THROW(StringBuffer(0));
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testConstructorString() {

    StringBuffer sb("fixture");
    CPPUNIT_ASSERT_EQUAL(String("fixture"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(String("fixture").length() + 16, sb.capacity());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendBoolean() {

    StringBuffer sb;
    sb.append(true);
    CPPUNIT_ASSERT_EQUAL(String("true"), sb.toString());
    sb.setLength(0);
    sb.append(false);
    CPPUNIT_ASSERT_EQUAL(String("false"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendChar() {
    StringBuffer sb;
    sb.append('a');
    CPPUNIT_ASSERT_EQUAL(String("a"), sb.toString());
    sb.setLength(0);
    sb.append('b');
    CPPUNIT_ASSERT_EQUAL(String("b"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendCharArray() {

    StringBuffer sb;
    sb.append("ab");
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());
    sb.setLength(0);
    sb.append("cd");
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a NullPointerException",
        sb.append((const char*) NULL),
        NullPointerException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendCharArrayIntInt() {

    StringBuffer sb;
    sb.append("ab", 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());
    sb.setLength(0);
    sb.append("cd");
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());

    sb.setLength(0);
    sb.append("abcd", 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());

    sb.setLength(0);
    sb.append("abcd", 2, 2);
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());

    sb.setLength(0);
    sb.append("abcd", 2, 0);
    CPPUNIT_ASSERT_EQUAL(String(""), sb.toString());

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a NullPointerException",
        sb.append((const char*) NULL, 0, 2),
        NullPointerException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.append("abcd", -1, 2),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.append("abcd", 0, -1),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.append("abcd", 2, 3),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendCharSequence() {

    String ab("ab");
    String cd("cd");

    StringBuffer sb;
    sb.append(&ab);
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());
    sb.setLength(0);
    sb.append(&cd);
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());
    sb.setLength(0);
    sb.append((CharSequence*) NULL);
    CPPUNIT_ASSERT_EQUAL(String("null"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendCharSequenceIntInt() {

    String ab("ab");
    String cd("cd");
    String abcd("abcd");

    StringBuffer sb;
    sb.append(&ab, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());
    sb.setLength(0);
    sb.append(&cd, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());
    sb.setLength(0);
    sb.append(&abcd, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());
    sb.setLength(0);
    sb.append(&abcd, 2, 4);
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());
    sb.setLength(0);
    sb.append((CharSequence*) NULL, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("nu"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendShort() {

    short a = 1;
    short b = 0;
    short c = -1;

    StringBuffer sb;
    sb.append(a);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(a), sb.toString());
    sb.setLength(0);
    sb.append(0);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(b), sb.toString());
    sb.setLength(0);
    sb.append(c);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(c), sb.toString());
    sb.setLength(0);
    sb.append(Short::MIN_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Short::MIN_VALUE), sb.toString());
    sb.setLength(0);
    sb.append(Short::MAX_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Short::MAX_VALUE), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendInt() {

    int a = 1;
    int b = 0;
    int c = -1;

    StringBuffer sb;
    sb.append(a);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(a), sb.toString());
    sb.setLength(0);
    sb.append(0);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(b), sb.toString());
    sb.setLength(0);
    sb.append(c);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(c), sb.toString());
    sb.setLength(0);
    sb.append(Integer::MIN_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Integer::MIN_VALUE), sb.toString());
    sb.setLength(0);
    sb.append(Integer::MAX_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Integer::MAX_VALUE), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendLong() {
    StringBuffer sb;
    sb.append(1LL);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(1LL), sb.toString());
    sb.setLength(0);
    sb.append(0LL);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(0LL), sb.toString());
    sb.setLength(0);
    sb.append(-1LL);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(-1LL), sb.toString());
    sb.setLength(0);
    sb.append(Integer::MIN_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Integer::MIN_VALUE), sb.toString());
    sb.setLength(0);
    sb.append(Integer::MAX_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Integer::MAX_VALUE), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendDouble() {
    StringBuffer sb;
    sb.append(1.0);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(1.0), sb.toString());
    sb.setLength(0);
    sb.append(0.0);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(0.0), sb.toString());
    sb.setLength(0);
    sb.append(-1.0);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(-1.0), sb.toString());
    sb.setLength(0);
    sb.append(Double::NaN);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Double::NaN), sb.toString());
    sb.setLength(0);
    sb.append(Double::NEGATIVE_INFINITY);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Double::NEGATIVE_INFINITY), sb.toString());
    sb.setLength(0);
    sb.append(Double::POSITIVE_INFINITY);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Double::POSITIVE_INFINITY), sb.toString());
    sb.setLength(0);
    sb.append(Double::MIN_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Double::MIN_VALUE), sb.toString());
    sb.setLength(0);
    sb.append(Double::MAX_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Double::MAX_VALUE), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendFloat() {
    StringBuffer sb;
    sb.append(1.0f);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(1.0f), sb.toString());
    sb.setLength(0);
    sb.append(0.0f);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(0.0f), sb.toString());
    sb.setLength(0);
    sb.append(-1.0f);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(-1.0f), sb.toString());
    sb.setLength(0);
    sb.append(Float::NaN);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Float::NaN), sb.toString());
    sb.setLength(0);
    sb.append(Float::NEGATIVE_INFINITY);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Float::NEGATIVE_INFINITY), sb.toString());
    sb.setLength(0);
    sb.append(Float::POSITIVE_INFINITY);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Float::POSITIVE_INFINITY), sb.toString());
    sb.setLength(0);
    sb.append(Float::MIN_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Float::MIN_VALUE), sb.toString());
    sb.setLength(0);
    sb.append(Float::MAX_VALUE);
    CPPUNIT_ASSERT_EQUAL(String::valueOf(Float::MAX_VALUE), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendString() {
    StringBuffer sb;
    sb.append(String("ab"));
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());
    sb.setLength(0);
    sb.append(String("cd"));
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendStringBuilder() {

    StringBuffer sb;
    sb.append(StringBuilder("ab"));
    CPPUNIT_ASSERT_EQUAL(String("ab"), sb.toString());
    sb.setLength(0);
    sb.append(StringBuilder("cd"));
    CPPUNIT_ASSERT_EQUAL(String("cd"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
namespace {

    class MyObject {
    public:

        String toString() const {
            return "MyObject";
        }

    };

}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendRawPointer() {

    MyObject obj;
    StringBuffer sb;
    sb.append(&obj);
    CPPUNIT_ASSERT_EQUAL(String("MyObject"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testAppendPointer() {

    Pointer<MyObject> obj(new MyObject);
    StringBuffer sb;
    sb.append(obj);
    CPPUNIT_ASSERT_EQUAL(String("MyObject"), sb.toString());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testCapacity() {
    StringBuffer sb;
    CPPUNIT_ASSERT_EQUAL(16, sb.capacity());
    sb.append("0123456789ABCDEF0123456789ABCDEF");
    CPPUNIT_ASSERT(sb.capacity() > 16);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testCharAt() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);

    for (int i = 0; i < fixture.length(); i++) {
        CPPUNIT_ASSERT_EQUAL((char) ('0' + i), sb.charAt(i));
    }

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.charAt(-1),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.charAt(fixture.length()),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.charAt(fixture.length() + 1),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testDeleteRange() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);

    sb.deleteRange(0, 0);
    CPPUNIT_ASSERT_EQUAL(fixture, sb.toString());
    sb.deleteRange(5, 5);
    CPPUNIT_ASSERT_EQUAL(fixture, sb.toString());
    sb.deleteRange(0, 1);
    CPPUNIT_ASSERT_EQUAL(String("123456789"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(9, sb.length());
    sb.deleteRange(0, sb.length());
    CPPUNIT_ASSERT_EQUAL(String(""), sb.toString());
    CPPUNIT_ASSERT_EQUAL(0, sb.length());

    {
        StringBuffer sb(fixture);
        sb.deleteRange(0, 11);
        CPPUNIT_ASSERT_EQUAL(String(""), sb.toString());
        CPPUNIT_ASSERT_EQUAL(0, sb.length());
    }

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        StringBuffer(fixture).deleteRange(-1, 2),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        StringBuffer(fixture).deleteRange(13, 12),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        StringBuffer(fixture).deleteRange(11, 12),
        StringIndexOutOfBoundsException);

    {
        StringBuffer sb;
        sb.append("abcde");
        String str = sb.toString();
        sb.deleteRange(0, sb.length());
        sb.append("YY");
        CPPUNIT_ASSERT_EQUAL(String("abcde"), str);
        CPPUNIT_ASSERT_EQUAL(String("YY"), sb.toString());
    }
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testDeleteCharAt() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);

    sb.deleteCharAt(0);
    CPPUNIT_ASSERT_EQUAL(String("123456789"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(9, sb.length());
    {
        StringBuffer sb(fixture);
        sb.deleteCharAt(5);
        CPPUNIT_ASSERT_EQUAL(String("012346789"), sb.toString());
        CPPUNIT_ASSERT_EQUAL(9, sb.length());
    }
    {
        StringBuffer sb(fixture);
        sb.deleteCharAt(9);
        CPPUNIT_ASSERT_EQUAL(String("012345678"), sb.toString());
        CPPUNIT_ASSERT_EQUAL(9, sb.length());
    }

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        StringBuffer(fixture).deleteCharAt(-1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        StringBuffer(fixture).deleteCharAt(fixture.length()),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        StringBuffer(fixture).deleteCharAt(fixture.length() + 1),
        StringIndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testEnsureCapacity() {

    StringBuffer sb(5);
    CPPUNIT_ASSERT_EQUAL(5, sb.capacity());
    sb.ensureCapacity(10);
    CPPUNIT_ASSERT_EQUAL(12, sb.capacity());
    sb.ensureCapacity(26);
    CPPUNIT_ASSERT_EQUAL(26, sb.capacity());
    sb.ensureCapacity(55);
    CPPUNIT_ASSERT_EQUAL(55, sb.capacity());
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testGetChars() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);
    char* dst = new char[10];
    sb.getChars(0, 10, dst, 10, 0);
    for (int i = 0; i < 10; ++i) {
        CPPUNIT_ASSERT_EQUAL(dst[i], fixture.charAt(i));
    }

    Arrays::fill(dst, 10, '\0');
    sb.getChars(0, 5, dst, 10, 0);
    char* fixtureChars = new char[10];
    for (int i = 0; i < 5; ++i) {
        CPPUNIT_ASSERT_EQUAL(dst[i], fixture.charAt(i));
    }

    Arrays::fill(dst, 10, '\0');
    Arrays::fill(fixtureChars, 10, '\0');
    sb.getChars(0, 5, dst, 10, 5);
    fixture.getChars(0, 5, fixtureChars, 10, 5);
    for (int i = 0; i < 10; ++i) {
        CPPUNIT_ASSERT_EQUAL(dst[i], fixtureChars[i]);
    }

    Arrays::fill(dst, 10, '\0');
    Arrays::fill(fixtureChars, 10, '\0');
    sb.getChars(5, 10, dst, 10, 1);
    fixture.getChars(5, 10, fixtureChars, 10, 1);
    for (int i = 0; i < 10; ++i) {
        CPPUNIT_ASSERT_EQUAL(dst[i], fixtureChars[i]);
    }

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.getChars(0, 10, dst, -1, 0),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a NullPointerException",
        sb.getChars(0, 10, (char*) NULL, 10, 0),
        NullPointerException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.getChars(-1, 10, dst, 10, 0),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.getChars(0, 10, dst, 10, -1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.getChars(5, 4, dst, 10, 0),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.getChars(0, 11, dst, 10, 0),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.getChars(0, 10, dst, 10, 5),
        StringIndexOutOfBoundsException);

    delete [] dst;
    delete [] fixtureChars;
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testIndexOfString() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);

    CPPUNIT_ASSERT_EQUAL(0, sb.indexOf("0"));
    CPPUNIT_ASSERT_EQUAL(0, sb.indexOf("012"));
    CPPUNIT_ASSERT_EQUAL(-1, sb.indexOf("02"));
    CPPUNIT_ASSERT_EQUAL(8, sb.indexOf("89"));
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testIndexOfStringInt() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);
    CPPUNIT_ASSERT_EQUAL(0, sb.indexOf("0"));
    CPPUNIT_ASSERT_EQUAL(0, sb.indexOf("012"));
    CPPUNIT_ASSERT_EQUAL(-1, sb.indexOf("02"));
    CPPUNIT_ASSERT_EQUAL(8, sb.indexOf("89"));

    CPPUNIT_ASSERT_EQUAL(0, sb.indexOf("0", 0));
    CPPUNIT_ASSERT_EQUAL(0, sb.indexOf("012", 0));
    CPPUNIT_ASSERT_EQUAL(-1, sb.indexOf("02", 0));
    CPPUNIT_ASSERT_EQUAL(8, sb.indexOf("89", 0));

    CPPUNIT_ASSERT_EQUAL(-1, sb.indexOf("0", 5));
    CPPUNIT_ASSERT_EQUAL(-1, sb.indexOf("012", 5));
    CPPUNIT_ASSERT_EQUAL(-1, sb.indexOf("02", 0));
    CPPUNIT_ASSERT_EQUAL(8, sb.indexOf("89", 5));
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testLastIndexOfString() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);
    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("0"));
    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("012"));
    CPPUNIT_ASSERT_EQUAL(-1, sb.lastIndexOf("02"));
    CPPUNIT_ASSERT_EQUAL(8, sb.lastIndexOf("89"));
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testLastIndexOfStringInt() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);
    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("0"));
    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("012"));
    CPPUNIT_ASSERT_EQUAL(-1, sb.lastIndexOf("02"));
    CPPUNIT_ASSERT_EQUAL(8, sb.lastIndexOf("89"));

    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("0", 0));
    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("012", 0));
    CPPUNIT_ASSERT_EQUAL(-1, sb.lastIndexOf("02", 0));
    CPPUNIT_ASSERT_EQUAL(8, sb.lastIndexOf("89", 10));

    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("0", 5));
    CPPUNIT_ASSERT_EQUAL(0, sb.lastIndexOf("012", 5));
    CPPUNIT_ASSERT_EQUAL(-1, sb.lastIndexOf("02", 0));
    CPPUNIT_ASSERT_EQUAL(-1, sb.lastIndexOf("89", 5));
}

////////////////////////////////////////////////////////////////////////////////
namespace {

    void reverseTest(const String& org, const String& rev, const String& back) {

        // create non-shared StringBuffer
        StringBuffer sb1(org);
        sb1.reverse();
        String reversed = sb1.toString();
        CPPUNIT_ASSERT_EQUAL(rev, reversed);

        // create non-shared StringBuffer
        StringBuffer sb2(reversed);
        sb2.reverse();
        reversed = sb2.toString();
        CPPUNIT_ASSERT_EQUAL(back, reversed);

        // test algorithm when StringBuffer is shared
        StringBuffer sb3(org);
        String copy = sb3.toString();
        CPPUNIT_ASSERT_EQUAL(org, copy);
        sb3.reverse();
        reversed = sb3.toString();
        CPPUNIT_ASSERT_EQUAL(rev, reversed);
        StringBuffer sb4(reversed);
        copy = sb4.toString();
        CPPUNIT_ASSERT_EQUAL(rev, copy);
        sb4.reverse();
        reversed = sb4.toString();
        CPPUNIT_ASSERT_EQUAL(back, reversed);
    }
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testReverse() {

    String fixture = "0123456789";
    StringBuffer sb1(fixture);
    sb1.reverse();
    CPPUNIT_ASSERT_EQUAL(String("9876543210"), sb1.toString());

    StringBuffer sb("012345678");
    sb.reverse();
    CPPUNIT_ASSERT_EQUAL(String("876543210"), sb.toString());
    sb.setLength(1);
    sb.reverse();
    CPPUNIT_ASSERT_EQUAL(String("8"), sb.toString());
    sb.setLength(0);
    sb.reverse();
    CPPUNIT_ASSERT_EQUAL(String(""), sb.toString());

    String str;
    str = "a";
    reverseTest(str, str, str);

    str = "ab";
    reverseTest(str, "ba", str);

    str = "abcdef";
    reverseTest(str, "fedcba", str);

    str = "abcdefg";
    reverseTest(str, "gfedcba", str);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testSubSequence() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);
    Pointer<CharSequence> ss(sb.subSequence(0, 5));
    CPPUNIT_ASSERT_EQUAL(std::string("01234"), ss->toString());

    ss.reset(sb.subSequence(0, 0));
    CPPUNIT_ASSERT_EQUAL(std::string(""), ss->toString());

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.subSequence(-1, 1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.subSequence(0, fixture.length() + 1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.subSequence(0, -1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.subSequence(3, 2),
        StringIndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testSubstringInt() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);
    String ss = sb.substring(0);
    CPPUNIT_ASSERT_EQUAL(fixture, ss);

    ss = sb.substring(10);
    CPPUNIT_ASSERT_EQUAL(String(""), ss);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.substring(-1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.substring(fixture.length() + 1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.substring(0, -1),
        StringIndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testSubstringIntInt() {

    String fixture = "0123456789";
    StringBuffer sb(fixture);
    String ss = sb.substring(0, 5);
    CPPUNIT_ASSERT_EQUAL(String("01234"), ss);

    ss = sb.substring(0, 0);
    CPPUNIT_ASSERT_EQUAL(String(), ss);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.substring(-1, 1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.substring(0, fixture.length() + 1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.substring(0, -1),
        StringIndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a StringIndexOutOfBoundsException",
        sb.substring(3, 2),
        StringIndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertChar() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, 'a');
    CPPUNIT_ASSERT_EQUAL(String("a0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, 'b');
    CPPUNIT_ASSERT_EQUAL(String("b0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, 'b');
    CPPUNIT_ASSERT_EQUAL(String("00b00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, 'b');
    CPPUNIT_ASSERT_EQUAL(String("0000b"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, 'a'),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, 'a'),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertBoolean() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, true);
    CPPUNIT_ASSERT_EQUAL(String("true0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(8, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, false);
    CPPUNIT_ASSERT_EQUAL(String("false0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(9, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, false);
    CPPUNIT_ASSERT_EQUAL(String("00false00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(9, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, false);
    CPPUNIT_ASSERT_EQUAL(String("0000false"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(9, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, false),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, false),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertCharArray() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, "ab");
    CPPUNIT_ASSERT_EQUAL(String("ab0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, "ab");
    CPPUNIT_ASSERT_EQUAL(String("00ab00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, "ab");
    CPPUNIT_ASSERT_EQUAL(String("0000ab"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a NullPointerException",
        sb.insert(0, (const char*) NULL),
        NullPointerException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, "Test"),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, "Test"),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertCharArrayWithOffset() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, "ab", 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("ab0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, "ab", 0, 1);
    CPPUNIT_ASSERT_EQUAL(String("a0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, "ab", 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("00ab00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, "ab", 0, 1);
    CPPUNIT_ASSERT_EQUAL(String("00a00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, "ab", 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("0000ab"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, "ab", 0, 1);
    CPPUNIT_ASSERT_EQUAL(String("0000a"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a NullPointerException",
        sb.insert(0, (const char*) NULL, 0, 2),
        NullPointerException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, "ab", 0, 2),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, "ab", 0, 2),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(4, "ab", 0, -1),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(4, "ab", -1, 2),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(4, "ab", 0, 3),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertString() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, String("fixture"));
    CPPUNIT_ASSERT_EQUAL(String("fixture0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(11, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, String("fixture"));
    CPPUNIT_ASSERT_EQUAL(String("00fixture00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(11, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, String("fixture"));
    CPPUNIT_ASSERT_EQUAL(String("0000fixture"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(11, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, String("fixture")),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, String("fixture")),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertStdString() {

    std::string fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, std::string("fixture"));
    CPPUNIT_ASSERT_EQUAL(String("fixture0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(11, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, std::string("fixture"));
    CPPUNIT_ASSERT_EQUAL(String("00fixture00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(11, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, std::string("fixture"));
    CPPUNIT_ASSERT_EQUAL(String("0000fixture"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(11, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, std::string("fixture")),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, std::string("fixture")),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertCharSequence() {

    String fixture = "0000";
    String ab("ab");
    StringBuffer sb(fixture);
    sb.insert(0, &ab);
    CPPUNIT_ASSERT_EQUAL(String("ab0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, &ab);
    CPPUNIT_ASSERT_EQUAL(String("00ab00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, &ab);
    CPPUNIT_ASSERT_EQUAL(String("0000ab"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, (CharSequence*) NULL);
    CPPUNIT_ASSERT_EQUAL(String("0000null"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(8, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, &ab),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, &ab),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertCharSequenceIntInt() {

    String fixture = "0000";
    String ab("ab");
    StringBuffer sb(fixture);
    sb.insert(0, &ab, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("ab0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, &ab, 0, 1);
    CPPUNIT_ASSERT_EQUAL(String("a0000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, &ab, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("00ab00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, &ab, 0, 1);
    CPPUNIT_ASSERT_EQUAL(String("00a00"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, &ab, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("0000ab"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, &ab, 0, 1);
    CPPUNIT_ASSERT_EQUAL(String("0000a"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, (CharSequence*) NULL, 0, 2);
    CPPUNIT_ASSERT_EQUAL(String("0000nu"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, &ab, 0, 2),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, &ab, 0, 2),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, &ab, -1, 2),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, &ab, 0, -1),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, &ab, 0, 3),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertDouble() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, -1.1);
    CPPUNIT_ASSERT_EQUAL(String("-1.10000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(8, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, 0.1);
    CPPUNIT_ASSERT_EQUAL(String("0.10000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(7, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, 1.1);
    CPPUNIT_ASSERT_EQUAL(String("001.100"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(7, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, 2.1);
    CPPUNIT_ASSERT_EQUAL(String("00002.1"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(7, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, 1.0),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, 1.0),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertFloat() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, -1.1f);
    CPPUNIT_ASSERT_EQUAL(String("-1.10000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(8, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, 0.1f);
    CPPUNIT_ASSERT_EQUAL(String("0.10000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(7, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, 1.1f);
    CPPUNIT_ASSERT_EQUAL(String("001.100"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(7, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, 2.1f);
    CPPUNIT_ASSERT_EQUAL(String("00002.1"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(7, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, 1.0f),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, 1.0f),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertShort() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, (short) -1);
    CPPUNIT_ASSERT_EQUAL(String("-10000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, (short) 0);
    CPPUNIT_ASSERT_EQUAL(String("00000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, (short) 1);
    CPPUNIT_ASSERT_EQUAL(String("00100"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, (short) 2);
    CPPUNIT_ASSERT_EQUAL(String("00002"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, (short) 1),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, (short) 1),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertInt() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, -1);
    CPPUNIT_ASSERT_EQUAL(String("-10000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, 0);
    CPPUNIT_ASSERT_EQUAL(String("00000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, 1);
    CPPUNIT_ASSERT_EQUAL(String("00100"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, 2);
    CPPUNIT_ASSERT_EQUAL(String("00002"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, 1),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, 1),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertLong() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.insert(0, -1LL);
    CPPUNIT_ASSERT_EQUAL(String("-10000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(0, 0LL);
    CPPUNIT_ASSERT_EQUAL(String("00000"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(2, 1LL);
    CPPUNIT_ASSERT_EQUAL(String("00100"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.insert(4, 2LL);
    CPPUNIT_ASSERT_EQUAL(String("00002"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, 1LL),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, 1LL),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertRawPointer() {

    String fixture = "0000";
    MyObject obj;
    StringBuffer sb;
    sb.insert(0, &obj);
    CPPUNIT_ASSERT_EQUAL(String("MyObject"), sb.toString());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, 1LL),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, 1LL),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testInsertPointer() {

    String fixture = "0000";
    Pointer<MyObject> obj(new MyObject);
    StringBuffer sb;
    sb.insert(0, obj);
    CPPUNIT_ASSERT_EQUAL(String("MyObject"), sb.toString());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(-1, obj),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.insert(5, obj),
        IndexOutOfBoundsException);
}

////////////////////////////////////////////////////////////////////////////////
void StringBufferTest::testReplace() {

    String fixture = "0000";
    StringBuffer sb(fixture);
    sb.replace(1, 3, "11");
    CPPUNIT_ASSERT_EQUAL(String("0110"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(4, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.replace(1, 2, "11");
    CPPUNIT_ASSERT_EQUAL(String("01100"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(5, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.replace(4, 5, "11");
    CPPUNIT_ASSERT_EQUAL(String("000011"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);
    sb.replace(4, 6, "11");
    CPPUNIT_ASSERT_EQUAL(String("000011"), sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, sb.length());
    sb.setLength(0);
    sb.append(fixture);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a NullPointerException",
        sb.replace(1, 2, (const char*) NULL),
        NullPointerException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.replace(-1, 2, "11"),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.replace(5, 2, "11"),
        IndexOutOfBoundsException);

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should have thrown a IndexOutOfBoundsException",
        sb.replace(3, 2, "11"),
        IndexOutOfBoundsException);

    StringBuffer buffer("1234567");
    buffer.replace(2, 6, "XXX");
    CPPUNIT_ASSERT_EQUAL(String("12XXX7"), buffer.toString());
}
