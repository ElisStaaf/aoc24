#!/bin/sh

TMPL="scripts/tmpl"

mkdir "day-$1"

cat "$TMPL/MAKE" >> "day-$1/Makefile"
cat "$TMPL/DEFS" >> "day-$1/defs.h"

touch "day-$1/input.txt"
touch "day-$1/part1.c"
touch "day-$1/part2.c"
