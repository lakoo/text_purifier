/******************************************************************************
 * Copyright (C) 2017 Lakoo Games Ltd.                                        *
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
 * @file   test_textpurifier.h
 * @author Aludirk Wong
 * @date   2017-07-21
 */

#ifndef __LAKOO_TEST_TEXTPURIFIER_H__
#define __LAKOO_TEST_TEXTPURIFIER_H__

#include <algorithm>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <list>
#include <memory>
#include <vector>

#include <cppunit/extensions/HelperMacros.h>

#include "text_purifier.h"


namespace CppUnit
{
    template<>
    struct assertion_traits<const char*>
    {
        static bool equal(const char* const& lhs, const char* const& rhs)
        {
            return strcmp(lhs, rhs) == 0;
        }

        static std::string toString(const char* const& str)
        {
            return std::string(str);
        }
    };

    template<>
    struct assertion_traits<const wchar_t*>
    {
        static bool equal(const wchar_t* const& lhs, const wchar_t* const& rhs)
        {
            return wcscmp(lhs, rhs) == 0;
        }

        static std::string toString(const wchar_t* const& str)
        {
            const char* const locale = setlocale(LC_ALL, "C.UTF-8");
            const std::size_t size = std::wcstombs(nullptr, str, 0) + 1;

            std::vector<char> cStr(size);
            std::memset(cStr.data(), 0, size);
            std::wcstombs(cStr.data(), str, size);

            setlocale(LC_ALL, locale);
            return std::string(cStr.begin(), cStr.end());
        }
    };

    template<>
    struct assertion_traits<std::wstring>
    {
        static bool equal(const std::wstring& lhs, const std::wstring& rhs)
        {
            return lhs == rhs;
        }

        static std::string toString(const std::wstring& str)
        {
            return assertion_traits<const wchar_t*>::toString(str.c_str());
        }
    };
}


namespace TestUtil
{
    template <typename _Type>
    struct is_raw_string {};
    template <> struct is_raw_string<char> { typedef char type; };
    template <> struct is_raw_string<wchar_t> { typedef wchar_t type; };

    template <typename _Type>
    struct is_std_string {};
    template <> struct is_std_string<std::string> { typedef std::string type; };
    template <> struct is_std_string<std::wstring> { typedef std::wstring type; };

    //--------------------------------------------------------------------------

    template <typename _Type>
    struct string_type { typedef _Type type; };
    template <> struct string_type<char> { typedef const char* type; };
    template <> struct string_type<wchar_t> { typedef const wchar_t* type; };

    //--------------------------------------------------------------------------

    #define STRING(_Type, _Str) getString<_Type>(_Str, L##_Str)

    template <typename _Type, typename = typename is_raw_string<_Type>::type>
    const _Type* getString(const char*, const wchar_t*);
    template <> const char* getString<char>(const char* c, const wchar_t*) { return c; }
    template <> const wchar_t* getString<wchar_t>(const char*, const wchar_t* wc) { return wc; }

    template <typename _Type, typename = typename is_std_string<_Type>::type>
    _Type getString(const char* c, const wchar_t* wc);
    template <> std::string getString<std::string>(const char* c, const wchar_t*) { return c; }
    template <> std::wstring getString<std::wstring>(const char*, const wchar_t* wc) { return wc; }

    //--------------------------------------------------------------------------

    #define CHARACTER(_Type, _Char) getCharacter<_Type>(_Char, L##_Char)

    template <typename _Type, typename = typename is_raw_string<_Type>::type>
    _Type getCharacter(char, wchar_t);
    template <> char getCharacter<char>(char c, wchar_t) { return c; }
    template <> wchar_t getCharacter<wchar_t>(char, wchar_t wc) { return wc; }

    template <typename _Type, typename = typename is_std_string<_Type>::type>
    typename _Type::value_type getCharacter(char, wchar_t);
    template <> char getCharacter<std::string>(char c, wchar_t) { return c; }
    template <> wchar_t getCharacter<std::wstring>(char, wchar_t wc) { return wc; }

    //--------------------------------------------------------------------------

    template <typename _Type, typename = typename is_raw_string<_Type>::type>
    _Type getMask();
    template <> char getMask<char>() { return '*'; }
    template <> wchar_t getMask<wchar_t>() { return L'禁'; }

    //--------------------------------------------------------------------------

    template <typename _Type, typename = typename is_std_string<_Type>::type>
    _Type replaceMask(const _Type& str)
    {
        _Type result(str);
        std::replace(result.begin(),
                     result.end(),
                     CHARACTER(_Type, '#'),
                     getMask<typename _Type::value_type>());
        return result;
    }

    template <typename _Type, typename = typename is_raw_string<_Type>::type>
    const _Type* replaceMask(const _Type* str)
    {
        static std::basic_string<_Type> buffer; // Only work for single thread.
        buffer = replaceMask(std::basic_string<_Type>(str));
        return buffer.c_str();
    }

    //--------------------------------------------------------------------------

    #define TEST_WORD_LIST(_Type) \
        STRING(_Type, "政治甲"), \
        STRING(_Type, "政治乙"), \
        STRING(_Type, "政治丙"), \
        STRING(_Type, "政治甲乙丙"), \
        STRING(_Type, "粗口甲"), \
        STRING(_Type, "粗口乙"), \
        STRING(_Type, "粗口丙"), \
        STRING(_Type, "粗口甲乙丙"), \
        STRING(_Type, "色情甲"), \
        STRING(_Type, "色情乙"), \
        STRING(_Type, "色情丙"), \
        STRING(_Type, "色情甲乙丙"), \
        STRING(_Type, " \r\n\t"), \
        STRING(_Type, "")

    template <typename _Type, typename = typename is_raw_string<_Type>::type>
    std::size_t makeList(const _Type* const*& result)
    {
        static const _Type* const list[] = { TEST_WORD_LIST(_Type) };
        // Only work for single thread.

        result = list;
        return std::extent<decltype(list)>::value;
    }

    template <typename _Type, typename = typename is_std_string<_Type>::type>
    std::size_t makeList(std::list<_Type>& result)
    {
        std::list<_Type> list { TEST_WORD_LIST(_Type) };
        result = std::move(list);
        return result.size();
    }

    template <typename _Type>
    std::vector<typename string_type<_Type>::type> makeVector()
    {
        std::vector<typename string_type<_Type>::type> vector { TEST_WORD_LIST(_Type) };
        return vector;
    }

    //--------------------------------------------------------------------------

    template <typename _Type, typename _MaskType>
    const _Type* purify(const lakoo::TextPurifier& tp, const _Type* str, const _MaskType* mask)
    {
        static std::basic_string<_Type> buffer; // Only work for single thread.

        const _Type* result = tp.purify(str, mask);
        buffer = result;
        tp.freePurifiedString(result);
        return buffer.c_str();
    }

    template <typename _Type, typename _MaskType>
    _Type& purify(const lakoo::TextPurifier& tp, _Type& str, const _MaskType* mask)
    {
        return tp.purify(str, mask);
    }

    template <typename _Type, typename _MaskType>
    _Type purify(const lakoo::TextPurifier& tp, const _Type& str, const _MaskType* mask)
    {
        return tp.purify(str, mask);
    }

    template <typename _Type, typename = typename is_std_string<_Type>::type>
    _Type& purify(const lakoo::TextPurifier& tp, _Type& str, const _Type& mask)
    {
        return tp.purify(str, mask);
    }

    template <typename _Type, typename = typename is_std_string<_Type>::type>
    _Type purify(const lakoo::TextPurifier& tp, const _Type& str, const _Type& mask)
    {
        return tp.purify(str, mask);
    }

    template <typename _Type, typename _MaskType>
    const _Type* purify(const lakoo::TextPurifier& tp,
                        const _Type* str,
                        _MaskType mask,
                        bool isMatchSize)
    {
        static std::basic_string<_Type> buffer; // Only work for single thread.

        const _Type* result = tp.purify(str, mask, isMatchSize);
        buffer = result;
        tp.freePurifiedString(result);
        return buffer.c_str();
    }

    template <typename _Type, typename _MaskType>
    _Type& purify(const lakoo::TextPurifier& tp, _Type& str, _MaskType mask, bool isMatchSize)
    {
        return tp.purify(str, mask, isMatchSize);
    }

    template <typename _Type, typename _MaskType>
    _Type purify(const lakoo::TextPurifier& tp, const _Type& str, _MaskType mask, bool isMatchSize)
    {
        return tp.purify(str, mask, isMatchSize);
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testEmpty(const lakoo::TextPurifier& tp)
    {
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "政治甲")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "政治乙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "政治丙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "政治甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "粗口甲")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "粗口乙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "粗口丙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "粗口甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "色情甲")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "色情乙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "色情丙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "色情甲乙丙")));
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testWordList(const lakoo::TextPurifier& tp)
    {
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "政治")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "粗口")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "色情")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "甲")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "乙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "丙")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "政治粗口色情")));
        CPPUNIT_ASSERT_EQUAL(false, tp.check(STRING(_Type, "甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "政治甲")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "政治乙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "政治丙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "政治甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "粗口甲")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "粗口乙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "粗口丙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "粗口甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "色情甲")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "色情乙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "色情丙")));
        CPPUNIT_ASSERT_EQUAL(true, tp.check(STRING(_Type, "色情甲乙丙")));
    }

    //--------------------------------------------------------------------------

    template <typename _Type, typename _MaskType>
    void testPurifyWithString(const lakoo::TextPurifier& tp, bool isConst = true)
    {
    #define TEST(test, mask, expected) \
        if(isConst) \
        { \
            typename string_type<_Type>::type result; \
            result = purify<_Type, _MaskType>(tp, STRING(_Type, test), STRING(_MaskType, mask)); \
            CPPUNIT_ASSERT_EQUAL(STRING(_Type, expected), result); \
        } \
        else \
        { \
            typename string_type<_Type>::type result(STRING(_Type, test)); \
            purify<_Type, _MaskType>(tp, result, STRING(_MaskType, mask)); \
            CPPUNIT_ASSERT_EQUAL(STRING(_Type, expected), result); \
        }

        TEST("", "*禁言*", "");
        TEST("政治粗口色情", "*禁言*", "政治粗口色情");
        TEST("甲乙丙", "*禁言*", "甲乙丙");
        TEST("ABC DEF GHI ＜政治一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜政治一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜政治甲＞ ＜政治乙＞ ＜政治丙＞ 政治甲乙丙 987 654 321",
             "禁言",
             "ABC DEF GHI ＜禁言＞ ＜禁言＞ ＜禁言＞ 禁言 987 654 321");
        TEST("ABC DEF GHI ＜政治甲＞ ＜政治乙＞ ＜政治丙＞ 政治甲乙丙 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜*禁言*＞ ＜*禁言*＞ ＜*禁言*＞ *禁言* 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             "禁言",
             "ABC DEF GHI ＜禁言＞ ＜禁言＞ ＜禁言＞ 禁言 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜*禁言*＞ ＜*禁言*＞ ＜*禁言*＞ *禁言* 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             "禁言",
             "ABC DEF GHI ＜禁言＞ ＜禁言＞ ＜禁言＞ 禁言 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜*禁言*＞ ＜*禁言*＞ ＜*禁言*＞ *禁言* 987 654 321");
        TEST("政治甲乙", "禁言", "禁言乙");
        TEST("政治甲乙", "*禁言*", "*禁言*乙");
        TEST("粗口甲乙", "禁言", "禁言乙");
        TEST("粗口甲乙", "*禁言*", "*禁言*乙");
        TEST("色情甲乙", "禁言", "禁言乙");
        TEST("色情甲乙", "*禁言*", "*禁言*乙");

    #undef TEST
    }

    //--------------------------------------------------------------------------

    template <typename _Type, typename _MaskType>
    void testPurifyWithCharacter(const lakoo::TextPurifier& tp, bool isConst = true)
    {
    #define TEST(test, isMatchSize, expectedFormat) \
        { \
            typename string_type<_Type>::type expected = \
                replaceMask(STRING(_Type, expectedFormat)); \
            if(isConst) \
            { \
                typename string_type<_Type>::type result; \
                result = purify<_Type, _MaskType>(tp, \
                                                  STRING(_Type, test), \
                                                  getMask<_MaskType>(), \
                                                  isMatchSize); \
                CPPUNIT_ASSERT_EQUAL(expected, result); \
            } \
            else \
            { \
                typename string_type<_Type>::type result(STRING(_Type, test)); \
                purify<_Type, _MaskType>(tp, result, getMask<_MaskType>(), isMatchSize); \
                CPPUNIT_ASSERT_EQUAL(expected, result); \
            } \
        }

        TEST("", true, "");
        TEST("", false, "");
        TEST("政治粗口色情", true, "政治粗口色情");
        TEST("政治粗口色情", false, "政治粗口色情");
        TEST("甲乙丙", true, "甲乙丙");
        TEST("甲乙丙", false, "甲乙丙");
        TEST("ABC DEF GHI ＜政治一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321",
             true,
             "ABC DEF GHI ＜政治一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜政治一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321",
             false,
             "ABC DEF GHI ＜政治一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321",
             true,
             "ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321",
             false,
             "ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜政治甲＞ ＜政治乙＞ ＜政治丙＞ 政治甲乙丙 987 654 321",
             true,
             "ABC DEF GHI ＜###＞ ＜###＞ ＜###＞ ##### 987 654 321");
        TEST("ABC DEF GHI ＜政治甲＞ ＜政治乙＞ ＜政治丙＞ 政治甲乙丙 987 654 321",
             false,
             "ABC DEF GHI ＜#＞ ＜#＞ ＜#＞ # 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             true,
             "ABC DEF GHI ＜###＞ ＜###＞ ＜###＞ ##### 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             false,
             "ABC DEF GHI ＜#＞ ＜#＞ ＜#＞ # 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             true,
             "ABC DEF GHI ＜###＞ ＜###＞ ＜###＞ ##### 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             false,
             "ABC DEF GHI ＜#＞ ＜#＞ ＜#＞ # 987 654 321");
        TEST("政治甲乙", true, "###乙");
        TEST("政治甲乙", false, "#乙");
        TEST("粗口甲乙", true, "###乙");
        TEST("粗口甲乙", false, "#乙");
        TEST("色情甲乙", true, "###乙");
        TEST("色情甲乙", false, "#乙");

    #undef TEST
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testRawInit()
    {
        const _Type* const* list;
        std::size_t count = makeList(list);
        testWordList<_Type>(lakoo::TextPurifier(list, count));
    }

    template <typename _Type>
    void testStdInit()
    {
        std::list<_Type> list;
        makeList(list);
        testWordList<_Type>(lakoo::TextPurifier(list));
    }

    template <typename _Type>
    void testInit();
    template <> void testInit<char>() { testRawInit<char>(); }
    template <> void testInit<wchar_t>() { testRawInit<wchar_t>(); }
    template <> void testInit<std::string>() { testStdInit<std::string>(); }
    template <> void testInit<std::wstring>() { testStdInit<std::wstring>(); }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testAddWord()
    {
        lakoo::TextPurifier tp;
        testEmpty<_Type>(tp);

        for(const typename string_type<_Type>::type& word : makeVector<_Type>())
        {
            tp.add(word);
        }

        testWordList<_Type>(tp);
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testAddRawList()
    {
        lakoo::TextPurifier tp;
        testEmpty<_Type>(tp);

        const _Type* const* list;
        std::size_t count = makeList(list);
        tp.add(list, count);
        testWordList<_Type>(tp);
    }

    template <typename _Type>
    void testAddStdList()
    {
        lakoo::TextPurifier tp;
        testEmpty<_Type>(tp);

        std::list<_Type> list;
        makeList(list);
        tp.add(list);
        testWordList<_Type>(tp);
    }

    template <typename _Type>
    void testAddList();
    template <> void testAddList<char>() { testAddRawList<char>(); }
    template <> void testAddList<wchar_t>() { testAddRawList<wchar_t>(); }
    template <> void testAddList<std::string>() { testAddStdList<std::string>(); }
    template <> void testAddList<std::wstring>() { testAddStdList<std::wstring>(); }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testRawPurify()
    {
        const _Type* const* list;
        const std::size_t count = makeList(list);
        lakoo::TextPurifier tp(list, count);

        testPurifyWithString<_Type, _Type>(tp);
        testPurifyWithCharacter<_Type, _Type>(tp);
    }

    template <typename _Type>
    void testStdPurify()
    {
        std::list<_Type> list;
        makeList(list);
        lakoo::TextPurifier tp(list);

        testPurifyWithString<_Type, _Type>(tp);
        testPurifyWithString<_Type, _Type>(tp, false);
        testPurifyWithString<_Type, typename _Type::value_type>(tp);
        testPurifyWithString<_Type, typename _Type::value_type>(tp, false);
        testPurifyWithCharacter<_Type, typename _Type::value_type>(tp);
        testPurifyWithCharacter<_Type, typename _Type::value_type>(tp, false);
    }

    template <typename _Type>
    void testPurify();
    template <> void testPurify<char>() { testRawPurify<char>(); }
    template <> void testPurify<wchar_t>() { testRawPurify<wchar_t>(); }
    template <> void testPurify<std::string>() { testStdPurify<std::string>(); }
    template <> void testPurify<std::wstring>() { testStdPurify<std::wstring>(); }
}

#endif // __LAKOO_TEST_TEXTPURIFIER_H__
