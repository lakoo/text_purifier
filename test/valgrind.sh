#!/usr/bin/env bash

which valgrind &> /dev/null
if [[ ${?} -ne 0 ]]; then
  printf "Can't find valgrind, skipping test.\n"
  exit 77
fi

# Due to the valgrind bug in Mac OSX, see https://bugs.kde.org/show_bug.cgi?id=382708
PLATFORM="$(uname -s | tr '[:upper:]' '[:lower:]')"
if [[ "${PLATFORM}" == "darwin" ]]; then
  printf "Due to valgrind bug in Mac OSX, skipping test.\n"
  exit 77
fi

pushd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null
valgrind --tool=memcheck --trace-children=yes --error-exitcode=1 --leak-check=full --track-origins=yes ./test
EXIT_CODE=${?}
popd &> /dev/null

exit ${EXIT_CODE}
