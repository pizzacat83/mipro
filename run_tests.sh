#!/usr/bin/env bash

set -eu

pushd $(dirname $0) >/dev/null

for file in tests/*; do
    echo [*] $file
    ./$file
done

popd >/dev/null
