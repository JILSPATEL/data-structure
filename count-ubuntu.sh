#!/usr/bin/env bash
# Run from repo root: ./count-cpp.sh

COUNT=$(find . -type f -name "*.cpp" | wc -l)
BADGE="![cpp files](https://img.shields.io/badge/.cpp%20files-${COUNT}-blue)"

sed -i "s|!\[cpp files\].*|$BADGE|" README.md

echo "Updated: $COUNT .cpp files"
