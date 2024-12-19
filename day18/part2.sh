#!/bin/bash
#
# Day 18, Part 2: bisect using part1.

set `wc -l input.txt`
high=$1
low=1024
gridSize=71

set -x
while [ $low -lt $high ]; do
    mid=$[ ($high + $low) / 2 ]
    if ./part1 $gridSize $mid < input.txt >/dev/null; then
        low=$[ $mid + 1 ]
    else
        high=$mid
    fi
done

echo -n "Midpoint is $mid, which corresponds to "
sed ${mid}p\;d < input.txt
