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
 * @file   string_utils.h
 * @author Aludirk Wong
 * @date   2017-07-09
 */

#ifndef __LAKOO_STRING_UTILS_H__
#define __LAKOO_STRING_UTILS_H__

#include <string>


namespace lakoo
{
    //! String utilities.
    namespace StringUtils
    {
        //! Replace all matched word in the given string.
        /**
         * @param [in] str  The string to replace.
         * @param [in] from The word to match.
         * @param [in] to   The replacing word.
         * @return          The replaced string.
         */
        std::wstring replace(std::wstring str, const std::wstring& from, const std::wstring& to);

        //! Trim whitespaces from left and right to the given string.
        /**
         * @param [in] str The string to trim.
         * @return         The trimmed string.
         */
        std::wstring trim(const std::wstring& str);

        //! Transform the given string to lower case.
        /**
         * @param [in] str The string to transform.
         * @return         The transformed string.
         */
        std::wstring toLowerCase(std::wstring str);

        //! Convert std::string to std::wstring.
        /**
         * @param [in] str The std::string to convert.
         * @return         The converted string.
         */
        std::wstring strToWStr(const std::string& str);

        //! Convert char string to std::wstring.
        /**
         * @param [in] str The char string to convert.
         * @return         The converted string.
         */
        std::wstring cStrToWStr(const char* str);

        //! Convert char string to wchar_t string.
        /**
         * @param [in] str The char string to convert.
         * @return         The converted string, must be freed with freeWcStr(const wchar_t*).
         */
        const wchar_t* cStrToWcStr(const char* str);

        //! Free the wchar_t string.
        /**
         * @sa cStrToWcStr(const char*)
         */
        void freeWcStr(const wchar_t* str);

        //! Convert std::wstring to std::string.
        /**
         * @param [in] str The std::wstring to convert.
         * @return         The converted string.
         */
        std::string wStrToStr(const std::wstring& str);

        //! Convert wchar_t string to char string.
        /**
         * @param [in] str The wchar_t string to convert.
         * @return         The converted string, must be freed with freeCStr(const char*).
         */
        const char* wcStrToCStr(const wchar_t* str);

        //! Free the char string.
        /**
         * @sa wcStrToCStr(const wchar_t*)
         */
        void freeCStr(const char* str);
    } // namespace StringUtils
} // namespace lakoo

#endif // __LAKOO_STRING_UTILS_H__
