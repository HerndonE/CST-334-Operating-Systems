#!/bin/bash
# 0, 6 values per thread
rm -f out.txt
./merge < test5.txt > out.txt
diff -w out.txt gold5.txt > diffs.txt
