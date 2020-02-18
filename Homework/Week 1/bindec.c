/* This program intakes binary values and
converts it to decimal values */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// max length input string
#define MAXSTR 25

// convert input binary string to a number

int main() {

   // user input string
   char s[MAXSTR+3];

   // prompt for input if input from terminal
   if (isatty(fileno(stdin))) {
       printf("> ");
   }

   // read input string; at most MAXSTR+1 chars accepted
   // Note: this is tricky. If we accept only MAXSTR chars,
   // we can't see if user entered more chars and they are
   // being dropped by fgets.
   fgets(s, MAXSTR+3, stdin);

   // check input length; n does not include final carriage return
   int n = strlen(s)-1;
   if (n > MAXSTR) {
     printf("input cannot be more than %d characters\n", MAXSTR);
     exit(1);
 }

   // convert s from a string in binary, to an int, and output

   // YOUR CODE HERE

   int decimalValue = 0;
   int power = 0;

   while (n > 0){
     int temp = n-1;

     if (s[temp] != '0' && s[temp] != '1'){ //if non integer is entered
       printf("input must contain only zeros and ones\n");
       exit(1);
     }
     else if (s[temp] == '1'){
       decimalValue = decimalValue + (1 << power); //instead of pow()
     }
     n--;
     power++;
   } // end of function
   printf("%d\n", decimalValue);
}
