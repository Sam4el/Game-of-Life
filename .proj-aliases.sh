#!/bin/bash

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"

alias compile='(cmake -B "$ROOT/build" && cmake --build "$ROOT/build")'
alias unitTest='(cd $ROOT && compile && cd "$ROOT/build" && ctest --output-on-failure)'
alias run='("$ROOT/build/gameOfLife")'
alias cleanBuild='rm -rf "$ROOT/build"'
