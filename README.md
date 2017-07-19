# Text Purifier (0.8.3)

- [Introduction](#introduction)
- [Compilation](#compilation)
  - [Static Library](#static-library)
  - [Shared Library](#shared-library)
- [License](#license)

## Introduction

This is a C++ library for purifying text from a list of words.  It supports UTF-8 string (std::wstirng, std::string, wchar_t\*, char\*).

## Compilation

### Static Library

To compile static library (.a):
```bash
git clone https://github.com/lakoo/text_purifier.git
cd text_purifier
make static
make install
```

The static library is located at `bin/libtextpurifier.a`.

### Shared Library

To compile shared library (.so):
```bash
git clone https://github.com/lakoo/text_purifier.git
cd text_purifier
make shared
make install
```

The shared library is located at `bin/libtextpurifier.so`.

## License

This software is licensed under the [GNU Lesser GPL v3 license](https://www.gnu.org/copyleft/lgpl.html). © 2017 Lakoo Games Limited
