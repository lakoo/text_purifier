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
 * @file   char_node.cpp
 * @author Aludirk Wong
 * @date   2017-07-10
 */

#include "char_node.h"


using namespace lakoo;
using namespace std;


CharNode::CharNode()
: CharNode(L'\0')
{
}

CharNode::CharNode(wchar_t character)
: _character(character)
, _isEndNode(false)
, _next()
{
}

CharNode::~CharNode()
{
    _next.clear();
}

shared_ptr<CharNode> CharNode::nextNode(wchar_t character) const
{
    if(_next.empty())
    {
        return shared_ptr<CharNode>(nullptr);
    }

    auto iter = _next.find(character);
    return _next.end() != iter ? iter->second : shared_ptr<CharNode>(nullptr);
}

shared_ptr<CharNode> CharNode::add(wchar_t character)
{
    auto iter = _next.find(character);
    if(_next.end() != iter)
    {
        return iter->second;
    }

    auto nextNode = make_shared<CharNode>(character);
    _next.insert(pair<wchar_t, shared_ptr<CharNode>>(character, nextNode));
    return nextNode;
}
