#!/usr/bin/env bash

set -eu

pushd $(dirname $0) >/dev/null

for file in *; do
    if [ "$file" = "$(basename $0)" ]; then
        continue;
    fi
    ./$file
done

popd >/dev/null
