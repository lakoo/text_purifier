#!/usr/bin/env bash

which cppcheck &> /dev/null
if [[ ${?} -ne 0 ]]; then
  printf "Can't find cppcheck, skipping test.\n"
  exit 77
fi

pushd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null
cppcheck -I ../include --quiet --force --std=c++11 --enable=all --error-exitcode=1 --suppress=missingIncludeSystem --inline-suppr ..
EXIT_CODE=${?}
popd &> /dev/null

exit ${EXIT_CODE}
