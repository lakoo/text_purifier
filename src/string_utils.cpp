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
 * @file   string_utils.cpp
 * @author Aludirk Wong
 * @date   2017-07-10
 */

#include "string_utils.h"

#include <algorithm>
#include <clocale>
#include <cstdlib>
#include <cstring>


using namespace lakoo;
using namespace lakoo::StringUtils;
using namespace std;


std::wstring StringUtils::replace(std::wstring str, const std::wstring& from, const std::wstring& to)
{
    wstring::size_type begin = 0UL;
    while((begin = str.find(from, begin)) != wstring::npos)
    {
        str.replace(begin, from.length(), to);
        begin += to.length();
    }
    return str;
}

std::wstring StringUtils::trim(const std::wstring& str)
{
    const wstring blank = L"\r\n\t ";
    const size_t begin = str.find_first_not_of(blank);
    const size_t end = str.find_last_not_of(blank);

    if(wstring::npos != begin || wstring::npos != end)
    {
        return str.substr(begin, end - begin + 1UL);
    }
    else
    {
        return L"";
    }
}

std::wstring StringUtils::toLowerCase(std::wstring str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::wstring StringUtils::strToWStr(const std::string& str)
{
    return cStrToWStr(str.c_str());
}

std::wstring StringUtils::cStrToWStr(const char* str)
{
    const wchar_t* wcStr = cStrToWcStr(str);
    wstring wStr(wcStr);
    freeWcStr(wcStr);

    return wStr;
}

const wchar_t* StringUtils::cStrToWcStr(const char* str)
{
    const char* const currentLocale = setlocale(LC_ALL, "C.UTF-8");
    const size_t size = mbstowcs(nullptr, str, 0UL) + 1UL;

    wchar_t* wcStr = new wchar_t[size];
    wmemset(wcStr, 0, size);
    mbstowcs(wcStr, str, size);

    setlocale(LC_ALL, currentLocale);
    return wcStr;
}

void StringUtils::freeWcStr(const wchar_t* str)
{
    if(nullptr != str)
    {
        delete [] str;
    }
}

std::string StringUtils::wStrToStr(const std::wstring& str)
{
    const char* cStr = wcStrToCStr(str.c_str());
    string sStr(cStr);
    freeCStr(cStr);

    return sStr;
}

const char* StringUtils::wcStrToCStr(const wchar_t* str)
{
    const char* const currentLocale = setlocale(LC_ALL, "C.UTF-8");
    const size_t size = wcstombs(nullptr, str, 0UL) + 1UL;

    char* cStr = new char[size];
    memset(cStr, 0, size);
    wcstombs(cStr, str, size);

    setlocale(LC_ALL, currentLocale);
    return cStr;
}

void StringUtils::freeCStr(const char* str)
{
    if(nullptr != str)
    {
        delete [] str;
    }
}
