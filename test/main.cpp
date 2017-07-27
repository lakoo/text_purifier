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
 * @file   test.cpp
 * @author Aludirk Wong
 * @date   2017-07-21
 */

#include <iostream>
#include <locale>
#include <string>
#include <vector>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


using namespace CppUnit;
using namespace std;


bool setGlobalLocale(const vector<string>& localeList)
{
    for(const string& localeName : localeList)
    {
        try
        {
            locale::global(locale(localeName.c_str()));
            return true;
        }
        catch(...)
        {
        }
    }

    return false;
}


int main(int, char*[])
{
    const vector<string> locale = {
        "C.UTF-8",
        "en_US.UTF-8",
        "zh_HK.UTF-8",
        "zh_TW.UTF-8",
        "zh_CN.UTF-8"};
    if(!setGlobalLocale(locale))
    {
        cerr << "No suitable locale (UTF-8) can be used." << endl;
        exit(2);
    }

    TextUi::TestRunner runner;
    TestFactoryRegistry& registry = TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());

    bool result = runner.run("", false);

    return result ? 0 : 1;
}
