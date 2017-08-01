# Text Purifier (1.0.0)

[![CircleCI](https://circleci.com/gh/lakoo/text_purifier.svg?style=svg)](https://circleci.com/gh/lakoo/text_purifier)
[![codecov](https://codecov.io/gh/lakoo/text_purifier/branch/master/graph/badge.svg)](https://codecov.io/gh/lakoo/text_purifier)

- [Introduction](#introduction)
- [Installation](#installation)
- [Example](#example)
- [Change Logs](#change-logs)
- [License](#license)

## Introduction

This is a C++ library for purifying text from a list of words.  It supports UTF-8 string (std::wstirng, std::string, wchar_t\*, char\*).

## Installation

```bash
git clone https://github.com/lakoo/text_purifier.git
cd text_purifier
./autogen.sh
./configure
make
make install
```

## Example

```C++
################
# example.cpp
################

#include <iostream>
#include <list>
#include <string>
#include <type_traits>

#include <text_purifier.h>


using namespace std;


void wStringExample()
{
    list<wstring> list = { L"歧視言論", L"粗口", L"色情圖片" };
    lakoo::TextPurifier tp(list);

    const wstring str1(L"這是歧視言論啊！");
    wcout << L"1.  " << str1 << L" -> " << tp.purify(str1, L"河蟹") << endl;

    wstring str2(L"這是粗口用語啊！");
    wcout << L"2.  " << str2 << L" -> ";
    tp.purify(str2, L"Hi, Auntie");
    wcout << str2 << endl;

    const wstring str3(L"這裏有歧視言論、粗口用語、色情圖片等等。");
    wcout << L"3.  " << str3 << L" -> " << tp.purify(str3, L'畢', true) << endl;
    wcout << L"4.  " << str3 << L" -> " << tp.purify(str3, L'禁', false) << endl;
}

void stringExample()
{
    list<string> list = { "歧視言論", "粗口", "色情圖片" };
    lakoo::TextPurifier tp;

    tp.add(list);

    const string str1("這是歧視言論啊！");
    cout << "5.  " << str1 << " -> " << tp.purify(str1, "河蟹") << endl;

    string str2("這是粗口用語啊！");
    cout << "6.  " << str2 << " -> ";
    tp.purify(str2, "Hi, Auntie");
    cout << str2 << endl;

    const string str3("這裏有歧視言論、粗口用語、色情圖片等等。");
    cout << "7.  " << str3 << " -> " << tp.purify(str3, '*', true) << endl;
    cout << "8.  " << str3 << " -> " << tp.purify(str3, '#', false) << endl;
}

void wcharExample()
{
    const wchar_t* list[] = { L"歧視言論", L"粗口", L"色情圖片" };
    lakoo::TextPurifier tp;

    tp.add(list, extent<decltype(list)>::value);

    const wchar_t strA[] = L"這是歧視言論啊！";
    const wchar_t* str = tp.purify(strA, L"河蟹");
    wcout << "9.  " << strA << L" -> " << str << endl;
    tp.freePurifiedString(str);
    str = nullptr;

    const wchar_t strB[] = L"這裏有歧視言論、粗口用語、色情圖片等等。";

    str = tp.purify(strB, L'畢', true);
    wcout << "10. " << strB << L" -> " << str << endl;
    tp.freePurifiedString(str);
    str = nullptr;

    str = tp.purify(strB, L'禁', false);
    wcout << "11. " << strB << L" -> " << str << endl;
    tp.freePurifiedString(str);
    str = nullptr;
}

void charExample()
{
    const char* list[] = { "歧視言論", "粗口", "色情圖片" };
    lakoo::TextPurifier tp;

    for(const char* const word : list)
    {
        tp.add(word);
    }

    const char strA[] = "這是歧視言論啊！";
    const char* str = tp.purify(strA, "河蟹");
    cout << "12. " << strA << " -> " << str << endl;
    tp.freePurifiedString(str);
    str = nullptr;

    const char strB[] = "這裏有歧視言論、粗口用語、色情圖片等等。";

    str = tp.purify(strB, '*', true);
    cout << "13. " << strB << " -> " << str << endl;
    tp.freePurifiedString(str);
    str = nullptr;

    str = tp.purify(strB, '#', false);
    cout << "14. " << strB << " -> " << str << endl;
    tp.freePurifiedString(str);
    str = nullptr;
}

int main(int, char*[])
{
    ios::sync_with_stdio(false);
    locale::global(locale("C.UTF-8"));
    wcout.imbue(locale("C.UTF-8"));

    cout << "std::wstring" << endl;
    wStringExample();
    cout << endl;

    cout << "std::string" << endl;
    stringExample();
    cout << endl;

    cout << "wchar_t" << endl;
    wcharExample();
    cout << endl;

    cout << "char" << endl;
    charExample();

    return 0;
}
}
```

```bash
$ g++ -o example.o -std=c++11 -c example.cpp
$ g++ -o example -ltextpurifier -Wl,-rpath,/usr/local/lib example.o
$ ./example
std::wstring
1.  這是歧視言論啊！ -> 這是河蟹啊！
2.  這是粗口用語啊！ -> 這是Hi, Auntie用語啊！
3.  這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有畢畢畢畢、畢畢用語、畢畢畢畢等等。
4.  這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有禁、禁用語、禁等等。

std::string
5.  這是歧視言論啊！ -> 這是河蟹啊！
6.  這是粗口用語啊！ -> 這是Hi, Auntie用語啊！
7.  這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有****、**用語、****等等。
8.  這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有#、#用語、#等等。

wchar_t
9.  這是歧視言論啊！ -> 這是河蟹啊！
10. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有畢畢畢畢、畢畢用語、畢畢畢畢等等。
11. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有禁、禁用語、禁等等。

char
12. 這是歧視言論啊！ -> 這是河蟹啊！
13. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有****、**用語、****等等。
14. 這裏有歧視言論、粗口用語、色情圖片等等。 -> 這裏有#、#用語、#等等。
```

## Change Logs

| Version | Change Logs |
|:-------:| ----------- |
| 1.0.0 | First release. |

## License

This software is licensed under the [GNU Lesser GPL v3 license](https://www.gnu.org/copyleft/lgpl.html). © 2017 Lakoo Games Limited
