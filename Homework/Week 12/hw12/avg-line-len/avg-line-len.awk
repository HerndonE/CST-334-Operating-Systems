#!/usr/bin/awk -f
# return average length of line in input file

# YOUR CODE HERE
BEGIN {
   numOfChars = 0;
   numOfLines = 0;
}

{
   if(length($0) >= 1)
   {
      numOfLines = numOfLines + 1
      numOfChars = numOfChars + length($0)
   }
}

END{
     avg = numOfChars/numOfLines
     printf("%d\n", avg);
}