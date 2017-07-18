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
 * @file   char_node.h
 * @author Aludirk Wong
 * @date   2017-07-09
 */

#ifndef __LAKOO_CHAR_NODE_H__
#define __LAKOO_CHAR_NODE_H__

#include <map>
#include <memory>


namespace lakoo
{
    class CharNode;


    //! The typedef for the map of CharNode.
    typedef std::map<wchar_t, std::shared_ptr<CharNode>> CharMap;


    //! A character node.
    class CharNode final
    {
    public:
        //! Default constructor.
        /**
         * The CharNode with null character.
         */
        CharNode();

        //! Implicit constructor with single character.
        /**
         * @param [in] character The character for the node.
         */
        explicit CharNode(wchar_t character);

        //! Destructor.
        ~CharNode();

        //! Deleted copy constructor.
        CharNode(const CharNode&) = delete;

        //! Deleted assignment operator.
        CharNode& operator=(const CharNode&) = delete;

    public:
        //! The character which the CharNode represent.
        /**
         * @return The character which the CharNode represent.
         */
        inline wchar_t character() const { return _character; }

        //! Whether the CharNode is an end node.
        /**
         * @return Whether the CharNode is an end node.
         * @sa CharNode::markEndNode
         */
        inline bool isEndNode() const { return _isEndNode; }

        //! To mark the CharNode to be an end node.
        /**
         * The CharNode will mark to be an end node if the character is the last character in the
         * word.
         */
        inline void markEndNode() { _isEndNode = true; }

    public:
        //! To retrieve the next code with the given character.
        /**
         * @param [in] character The character to find next node.
         * @return               The next CharNode, nullptr if it is not found.
         */
        std::shared_ptr<CharNode> nextNode(wchar_t character) const;

        //! To add the next character from this CharNode.
        /**
         * @param [in] character The character to add.
         * @return               The new next or existing CharNode.
         */
        std::shared_ptr<CharNode> add(wchar_t character);

    private:
        //! The stored character.
        wchar_t _character;

        //! Whether the node is an end node.
        bool _isEndNode;

        //! The container to store the next CharNode.
        CharMap _next;
    };
} // namespace lakoo

#endif // __LAKOO_CHAR_NODE_H__
