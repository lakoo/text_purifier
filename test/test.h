/******************************************************************************
 * Copyright (C) 2017 Lakoo Games Ltd.`                                       *
 *                                                                            *
 * This file is part of Text Purifier.                                        *
 *                                                                            *
 * Text Purifier is free software: you can redistribute it and/or modify it   *
 * under the terms of the GNU Lesser General Public License as published      *
 * by the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Text Purifier is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Lesser General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with Text Purifier.  If not, see <http://www.gnu.org/licenses/>.     *
 ******************************************************************************/

/**
 * @file   test.h
 * @author Aludirk Wong
 * @date   2017-07-21
 */

#ifndef __LAKOO_TEST_H__
#define __LAKOO_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

#include "test_util.h"


template <typename _Class, typename _Type>
class TestTextPurifier : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(_Class);
    CPPUNIT_TEST(testInit);
    CPPUNIT_TEST(testAddWord);
    CPPUNIT_TEST(testAddList);
    CPPUNIT_TEST(testPurify);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testInit()
    {
        TestUtil::testInit<_Type>();
    }

    void testAddWord()
    {
        TestUtil::testAddWord<_Type>();
    }

    void testAddList()
    {
        TestUtil::testAddList<_Type>();
    }

    void testPurify()
    {
        TestUtil::testPurify<_Type>();
    }
};

class TestWString : public TestTextPurifier<TestWString, std::wstring> {};
class TestString : public TestTextPurifier<TestString, std::string> {};
class TestWcStr : public TestTextPurifier<TestWcStr, wchar_t> {};
class TestCStr : public TestTextPurifier<TestCStr, char> {};

#endif // __LAKOO_TEST_H__
