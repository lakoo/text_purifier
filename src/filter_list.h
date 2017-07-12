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
 * @file   filter_list.h
 * @author Aludirk Wong
 * @date   2017-07-09
 */

#ifndef __LAKOO_FILTER_LIST_H__
#define __LAKOO_FILTER_LIST_H__

#include <list>
#include <memory>
#include <string>


namespace lakoo
{
    class CharNode;


    //! The data structure to indicate the word segment.
    struct WordSegment final
    {
    public:
        //! The start position of a word segment.
        std::wstring::size_type _start;

        //! The length of the word segment.
        std::size_t _length;

    public:
        //! Constructor.
        /**
         * @param [in] start  The start poition of a word segment.
         * @param [in] length The length of the word segment.
         */
        WordSegment(std::wstring::size_type start, std::size_t length);

        //! Default destructor.
        ~WordSegment() = default;

        //! Deleted copy constructor.
        WordSegment(const WordSegment&) = delete;

        //! Deleted assignment operator.
        WordSegment& operator=(const WordSegment&) = delete;
    };


    //! Store the list of words to filter.
    class FilterList final
    {
    public:
        //! Default constructor.
        FilterList();

        //! Constructor with a list of filter words.
        /**
         * @param [in] list The list of std::wstring to filter.
         */
        explicit FilterList(const std::list<std::wstring>& list);

        /**
         * @overload
         * @param [in] list The list of std::string to filter.
         */
        explicit FilterList(const std::list<std::string>& list);

        /**
         * @overload
         * @param [in] list  An array of wchar_t string to filter.
         * @param [in] count The number of words in the list.
         */
        explicit FilterList(const wchar_t* const* list, std::size_t count);

        /**
         * @overload
         * @param [in] list An array of char string to filter.
         * @param [in] count The number of words in the list.
         */
        explicit FilterList(const char* const* list, std::size_t count);

        //! Default destructor.
        ~FilterList() = default;

        //! Deleted copy constructor.
        FilterList(const FilterList&) = delete;

        //! Deleted assignment operator.
        FilterList& operator=(const FilterList&) = delete;

    public:
        //! To add a word to the list.
        /**
         * @param [in] str The std::wstring to add.
         */
        void add(const std::wstring& str);

        /**
         * @overload
         * @param [in] str The std::string to add.
         */
        void add(const std::string& str);

        /**
         * @overload
         * @param [in] str The wchar_t string to add.
         */
        void add(const wchar_t* str);

        /**
         * @overload
         * @param [in] str The char string to add.
         */
        void add(const char* str);

        //! To add a list of words to the list.
        /**
         * @param [in] list The list of std::wstring to add.
         */
        void add(const std::list<std::wstring>& list);

        /**
         * @overload
         * @param [in] list The list of std::string to add.
         */
        void add(const std::list<std::string>& list);

        /**
         * @overload
         * @param [in] list  The list of wchar_t shring to add.
         * @param [in] count The number of words in the list.
         */
        void add(const wchar_t* const* list, std::size_t count);

        /**
         * @overload
         * @param [in] list  The list of char string to add.
         * @param [in] count The number of words in the list.
         */
        void add(const char* const* list, std::size_t count);

        //! To find all word segments to filter.
        /**
         * @param [in] str The std::wstring to check.
         * @return         A list of word segments to filter.
         */
        std::list<WordSegment> find(const std::wstring& str) const;

    private:
        //! The root CharNode of the filter list.
        std::shared_ptr<CharNode> _root;
    };
}; // namespace lakoo

#endif // __LAKOO_FILTER_LIST_H__
