#!/bin/bash
# 1, 6 values per thread
rm -f out.txt
./merge < test4.txt > out.txt
diff -w out.txt gold4.txt > diffs.txt
