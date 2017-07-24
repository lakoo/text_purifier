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
 * @file   text_purifier.cpp
 * @author Aludirk Wong
 * @date   2017-07-11
 */

#include "text_purifier.h"

#include "filter_list.h"
#include "string_utils.h"


using namespace lakoo;
using namespace lakoo::StringUtils;
using namespace std;


TextPurifier::TextPurifier()
: _filterList(unique_ptr<FilterList>(new FilterList()))
{
}

TextPurifier::TextPurifier(const std::list<std::wstring>& list)
: _filterList(unique_ptr<FilterList>(new FilterList(list)))
{
}

TextPurifier::TextPurifier(const std::list<std::string>& list)
: _filterList(unique_ptr<FilterList>(new FilterList(list)))
{
}

TextPurifier::TextPurifier(const wchar_t* const* list, std::size_t count)
: _filterList(unique_ptr<FilterList>(new FilterList(list, count)))
{
}

TextPurifier::TextPurifier(const char* const* list, std::size_t count)
: _filterList(unique_ptr<FilterList>(new FilterList(list, count)))
{
}

TextPurifier::~TextPurifier()
{
}

void TextPurifier::add(const std::wstring& str)
{
    _filterList->add(str);
}

void TextPurifier::add(const std::string& str)
{
    _filterList->add(str);
}

void TextPurifier::add(const wchar_t* str)
{
    _filterList->add(str);
}

void TextPurifier::add(const char* str)
{
    _filterList->add(str);
}

void TextPurifier::add(const std::list<std::wstring>& list)
{
    _filterList->add(list);
}

void TextPurifier::add(const std::list<std::string>& list)
{
    _filterList->add(list);
}

void TextPurifier::add(const wchar_t* const* list, std::size_t count)
{
    _filterList->add(list, count);
}

void TextPurifier::add(const char* const* list, std::size_t count)
{
    _filterList->add(list, count);
}

std::wstring TextPurifier::purify(const std::wstring& str, const std::wstring& mask) const
{
    wstring result(str);
    return purify(result, mask);
}

std::wstring TextPurifier::purify(const std::wstring& str, const wchar_t* mask) const
{
    return purify(str, wstring(mask));
}

std::wstring TextPurifier::purify(const std::wstring& str, wchar_t mask, bool isMatchSize) const
{
    wstring result(str);
    return purify(result, mask, isMatchSize);
}

std::wstring& TextPurifier::purify(std::wstring& str, const std::wstring& mask) const
{
    for(const WordSegment& segment : _filterList->find(str))
    {
        str.replace(segment._start, segment._length, mask);
    }
    return str;
}

std::wstring& TextPurifier::purify(std::wstring& str, const wchar_t* mask) const
{
    // cppcheck-suppress returnTempReference
    return purify(str, wstring(mask));
}

std::wstring& TextPurifier::purify(std::wstring& str, wchar_t mask, bool isMatchSize) const
{
    if(isMatchSize)
    {
        for(const WordSegment& segment : _filterList->find(str))
        {
            str.replace(segment._start, segment._length, segment._length, mask);
        }
        return str;
    }
    else
    {
        // cppcheck-suppress returnTempReference
        return purify(str, wstring(1, mask));
    }
}

std::string TextPurifier::purify(const std::string& str, const std::string& mask) const
{
    wstring wStr = strToWStr(str);
    purify(wStr, strToWStr(mask));

    return wStrToStr(wStr);
}

std::string TextPurifier::purify(const std::string& str, const char* mask) const
{
    return purify(str, string(mask));
}

std::string TextPurifier::purify(const std::string& str, char mask, bool isMatchSize) const
{
    if(isMatchSize)
    {
        wstring wStr = strToWStr(str);
        purify(wStr, strToWStr(string(1, mask))[0], isMatchSize);

        return wStrToStr(wStr);
    }
    else
    {
        return purify(str, string(1, mask));
    }
}

std::string& TextPurifier::purify(std::string& str, const std::string& mask) const
{
    str = purify(const_cast<const string&>(str), mask);
    return str;
}

std::string& TextPurifier::purify(std::string& str, const char* mask) const
{
    str = purify(const_cast<const string&>(str), string(mask));
    return str;
}

std::string& TextPurifier::purify(std::string& str, char mask, bool isMatchSize) const
{
    str = purify(const_cast<const string&>(str), mask, isMatchSize);
    return str;
}

const wchar_t* TextPurifier::purify(const wchar_t* str, const wchar_t* mask) const
{
    wstring wStr(str);
    purify(wStr, wstring(mask));

    size_t size = wStr.length() + 1;
    wchar_t* wcStr = new wchar_t[size];
    wmemset(wcStr, 0, size);
    wcscpy(wcStr, wStr.c_str());
    return wcStr;
}

const wchar_t* TextPurifier::purify(const wchar_t* str, wchar_t mask, bool isMatchSize) const
{
    if(isMatchSize)
    {
        wstring wStr(str);
        purify(wStr, mask, isMatchSize);

        size_t size = wStr.length() + 1;
        wchar_t* wcStr = new wchar_t[size];
        wmemset(wcStr, 0, size);
        wcscpy(wcStr, wStr.c_str());
        return wcStr;
    }
    else
    {
        const wchar_t maskStr[2] = {mask, L'\0'};
        return purify(str, maskStr);
    }
}

void TextPurifier::freePurifiedString(const wchar_t* str) const
{
    if(nullptr != str)
    {
        delete [] str;
    }
}

const char* TextPurifier::purify(const char* str, const char* mask) const
{
    wstring wStr(cStrToWStr(str));
    purify(wStr, cStrToWStr(mask));

    return wcStrToCStr(wStr.c_str());
}

const char* TextPurifier::purify(const char* str, char mask, bool isMatchSize) const
{
    if(isMatchSize)
    {
        wstring wStr(cStrToWStr(str));
        purify(wStr, strToWStr(string(1, mask))[0], isMatchSize);

        return wcStrToCStr(wStr.c_str());
    }
    else
    {
        const char maskStr[2] = {mask, '\0'};
        return purify(str, maskStr);
    }
}

void TextPurifier::freePurifiedString(const char* str) const
{
    freeCStr(str);
}

bool TextPurifier::check(const std::wstring& str) const
{
    return _filterList->find(str).size() > 0;
}

bool TextPurifier::check(const std::string& str) const
{
    return check(strToWStr(str));
}

bool TextPurifier::check(const wchar_t* str) const
{
    return check(wstring(str));
}

bool TextPurifier::check(const char* str) const
{
    return check(cStrToWStr(str));
}
