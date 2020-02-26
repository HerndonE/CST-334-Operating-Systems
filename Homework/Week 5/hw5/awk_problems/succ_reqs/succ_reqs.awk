#!/usr/bin/awk -f
/Alloc/ {
    gsub(/\(|\)|Alloc/,"",$3)
    res = 0
    if ($5 != "-1"){
	res = 1
    }
    print $3" "res
}
