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
 * @file   text_purifier.h
 * @author Aludirk Wong
 * @date   2017-07-07
 */

#ifndef __LAKOO_TEXT_PURIFIER_H__
#define __LAKOO_TEXT_PURIFIER_H__

#include <list>
#include <memory>
#include <string>


//! The namespace for Lakoo library.
namespace lakoo
{
    class FilterList;;


    //! To purify text by given list of strings.
    class TextPurifier final
    {
    public:
        //! Default constructor.
        TextPurifier();

        //
        //! Constructor with a list of filter words.
        /**
         * @param [in] list The list of std::wstring to purify.
         */
        explicit TextPurifier(const std::list<std::wstring>& list);

        /**
         * @overload
         * @param [in] list The list of std::string to purify.
         */
        explicit TextPurifier(const std::list<std::string>& list);

        /**
         * @overload
         * @param [in] list An array of wchar_t string to purify.
         * @param [in] count The number of words in the list.
         */
        explicit TextPurifier(const wchar_t* const* list, std::size_t count);

        /**
         * @overload
         * @param [in] list An array of char string to purify.
         * @param [in] count The number of words in the list.
         */
        explicit TextPurifier(const char* const* list, std::size_t count);

        //! Default destructor.
        ~TextPurifier() = default;

        //! Deleted copy constructor.
        TextPurifier(const TextPurifier&) = delete;

        //! Deleted assignment operator.
        TextPurifier& operator=(const TextPurifier&) = delete;

    public:
        //! To add a word to the list to purify.
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

        //! To add a list of words to the list to purify.
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
         * @param [in] list The list of wchar_t string to add.
         * @param [in] count The number of words in the list.
         */
        void add(const wchar_t* const* list, std::size_t count);

        /**
         * @overload
         * @param [in] list The list of char string to add.
         * @param [in] count The number of words in the list.
         */
        void add(const char* const* list, std::size_t count);

        //! To purify the string with given mask.
        /**
         * @param [in,out] str  The std::wstring to purify.
         * @param [in]     mask The std::wstring mask.
         * @return              The purified string.
         */
        std::wstring& purify(std::wstring& str, const std::wstring& mask) const;

        /**
         * @overload
         * @param [in,out] str  The std::wstring to purify.
         * @param [in]     mask The wchar_t string mask.
         */
        std::wstring& purify(std::wstring& str, const wchar_t* mask) const;

        /**
         * @overload
         * @param [in,out] str         The std::wstring to purify.
         * @param [in]     mask        The wchar_t mask.
         * @param [in]     isMatchSize If isMatchSize is \c true, the mask will be repeated until
         *                             the same size with the purified word.
         */
        std::wstring& purify(std::wstring& str, wchar_t mask, bool isMatchSize) const;

        /**
         * @overload
         * @param [in] str  The std::string to purify.
         * @param [in] mask The std::string mask.
         */
        std::string purify(const std::string& str, const std::string& mask) const;

        /**
         * @overload
         * @param [in] str  The std::string to purify.
         * @param [in] mask The char string mask.
         */
        std::string purify(const std::string& str, const char* mask) const;

        /**
         * @overload
         * @param [in] str         The std::string to purify.
         * @param [in] mask        The char mask.
         * @param [in] isMatchSize If isMatchSize is \c true, the mask will be repeated until the
         *                         same size with the purified word.
         */
        std::string purify(const std::string& str, char mask, bool isMatchSize) const;

        //! To purify the string with given mask.
        /**
         * @param [in] str  The wchar_t string to purify.
         * @param [in] mask The wchar_t string mask.
         * @return          The purified string, must be free with
         *                  freePurifiedString(const wchar_t*) const.
         */
        const wchar_t* purify(const wchar_t* str, const wchar_t* mask) const;

        /**
         * @overload
         * @param [in] str         The wchar_t string to purify.
         * @param [in] mask        The wchar_t mask.
         * @param [in] isMatchSize If isMatchSize is \c true, the mask will be repeated until the
         *                         same size with the purified word.
         */
        const wchar_t* purify(const wchar_t* str, wchar_t mask, bool isMatchSize) const;

        //! To free the purified string from purify(const wchar_t*, const wchar_t*) const.
        /**
         * @param [in] str The string to free.
         */
        void freePurifiedString(const wchar_t* str) const;

        //! To purify the string with given mask.
        /**
         * @param [in] str  The char string to purify.
         * @param [in] mask The char string mask.
         * @return          The purified string, must be free with
         *                  freePurifiedString(const char*) const.
         */
        const char* purify(const char* str, const char* mask) const;

        /**
         * @overload
         * @param [in] str         The char string to purify.
         * @param [in] mask        The char mask.
         * @param [in] isMatchSize If isMatchSize is \c true, the mask will be repeated until the
         *                         same size with the purified word.
         */
        const char* purify(const char* str, char mask, bool isMatchSize) const;

        //! To free the purified string from purify(const char*, const char*) const.
        /**
         * @param [in] str The string to free.
         */
        void freePurifiedString(const char* str) const;

        //! Check whether the given string need to be purified.
        /**
         * @param [in] str The std::wstring to check.
         * @return         Whether the given string need to be purified.
         */
        bool check(const std::wstring& str) const;

        /**
         * @overload
         * @param [in] str The std::string to check.
         */
        bool check(const std::string& str) const;

        /**
         * @overload
         * @param [in] str The wchar_t string to check.
         */
        bool check(const wchar_t* str) const;

        /**
         * @overload
         * @param [in] str The char string to check.
         */
        bool check(const char* str) const;

    private:
        //! The filter list for purifying words.
        std::unique_ptr<FilterList> _filterList;
    };
}; // namespace lakoo

#endif // __LAKOO_TEXT_PURIFIER_H__
