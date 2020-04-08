#!/bin/bash
# 6 values each thread
rm -f out.txt
./merge < test3.txt > out.txt
diff -w out.txt gold3.txt > diffs.txt
