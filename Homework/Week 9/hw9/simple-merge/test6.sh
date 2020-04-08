#!/bin/bash
# large number of inputs
rm -f out.txt
./merge < test6.txt > out.txt
diff -w out.txt gold6.txt > diffs.txt
