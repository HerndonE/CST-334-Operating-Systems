#!/usr/bin/awk -f
BEGIN {
  printf("Identifier, \"Full name\",")
  arr[200]
  count = 0
}
{
  if (NF == 1) {
    if ($1 == "}") {
      count--;
    }
  }
  if (NF == 2) {
    arr[count] = substr($1, 2, 1)
    count++
  }
  if (NF == 3 || NF == 4) {
    for (e = 0; e < count; e++) {
      if (e == 0) {
        temp = arr[e]
      } else {
        temp = temp "_" arr[e]
      }
    }
    temp = temp "_" substr($1, 2, 1)
    printf("%s,", temp)
  }
}
END {
  printf("comments\n")
}
