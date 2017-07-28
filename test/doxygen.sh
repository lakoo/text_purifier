#!/usr/bin/env bash

which doxygen &> /dev/null
if [[ ${?} -ne 0 ]]; then
  printf "Can't find doxygen, skipping test.\n"
  exit 77
fi

pushd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null
doxygen Doxyfile 1> /dev/null
EXIT_CODE=${?}
popd &> /dev/null

exit ${EXIT_CODE}
