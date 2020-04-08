#!/bin/bash
# 3 values each thread
rm -f out.txt
./merge < test2.txt > out.txt
diff -w out.txt gold2.txt > diffs.txt
