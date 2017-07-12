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
 * @file   filter_list.cpp
 * @author Aludirk Wong
 * @date   2017-07-10
 */

#include "filter_list.h"

#include "char_node.h"
#include "string_utils.h"


using namespace lakoo;
using namespace lakoo::StringUtils;
using namespace std;


WordSegment::WordSegment(std::wstring::size_type start, std::size_t length)
: _start(start)
, _length(length)
{
}

FilterList::FilterList()
: _root(make_shared<CharNode>())
{
}

FilterList::FilterList(const std::list<std::wstring>& list)
: FilterList()
{
    add(list);
}

FilterList::FilterList(const std::list<std::string>& list)
: FilterList()
{
    add(list);
}

FilterList::FilterList(const wchar_t* const* list, std::size_t count)
: FilterList()
{
    add(list, count);
}

FilterList::FilterList(const char* const* list, std::size_t count)
: FilterList()
{
    add(list, count);
}

void FilterList::add(const std::wstring& str)
{
    wstring cleanUpStr = replace(str, L" ", L"");
    cleanUpStr = trim(cleanUpStr);
    cleanUpStr = toLowerCase(cleanUpStr);

    auto node = _root;
    for(auto character : cleanUpStr)
    {
        node = node->add(character);
    }

    if(node != _root)
    {
        node->markEndNode();
    }
}

void FilterList::add(const std::string& str)
{
    add(strToWStr(str));
}

void FilterList::add(const wchar_t* str)
{
    add(wstring(str));
}

void FilterList::add(const char* str)
{
    add(cStrToWStr(str));
}

void FilterList::add(const std::list<std::wstring>& list)
{
    for(const wstring& str : list)
    {
        add(str);
    }
}

void FilterList::add(const std::list<std::string>& list)
{
    for(const string& str : list)
    {
        add(str);
    }
}

void FilterList::add(const wchar_t* const* list, std::size_t count)
{
    for(size_t index = 0; index < count; ++index)
    {
        add(list[index]);
    }
}

void FilterList::add(const char* const* list, std::size_t count)
{
    for(size_t index = 0; index < count; ++index)
    {
        add(list[index]);
    }
}

std::list<WordSegment> FilterList::find(const std::wstring& str) const
{
    list<WordSegment> result;

    wstring charList = toLowerCase(str);
    wstring::size_type size = charList.size();
    for(size_t charIndex = 0; charIndex < size; ++charIndex)
    {
        if(L' ' == charList.at(charIndex))
        {
            continue;
        }

        auto nextNode = _root;
        size_t end = numeric_limits<size_t>::max();

        for(size_t findIndex = charIndex; findIndex < size; ++findIndex)
        {
            wchar_t ch = charList.at(findIndex);
            if(L' ' == ch)
            {
                continue;
            }

            nextNode = nextNode->nextNode(ch);
            if(!nextNode)
            {
                break;
            }

            if(nextNode->isEndNode())
            {
                end = findIndex;
            }
        }

        if(numeric_limits<size_t>::max() != end)
        {
            result.emplace_back(charIndex, end - charIndex + 1);
        }
    }

    return result;
}
