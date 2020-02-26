#!/usr/bin/awk -f

{
   if($1 == "Free"){
       for(i=1; i <= NF; i++){
           if($i ~ /sz:\d*/){
               size = substr($i,4);
               printf("%s ", size);
           }
       }
       printf("\n");
   }
}
