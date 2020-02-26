#!/usr/bin/awk -f
/Alloc/ {
    gsub(/\(|\)|Alloc/,"",$3)
    print $3
}
 
