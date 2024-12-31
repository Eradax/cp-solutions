#!/usr/bin/env bash

# g++ -fsanitize=undefined,address -g slottsmur-sqrt.cpp -O2 -o slottsmur
# g++ -fsanitize=undefined,address -g slottsmur-sqrt.cpp -O2 -o dbg -D DBG
#
# echo "Take input"

# LSAN_OPTIONS=suppressions=lsan.supp ./slottsmur
# LSAN_OPTIONS=detect_leaks=0 ./dbg
LSAN_OPTIONS=detect_leaks=0 ./slottsmur
