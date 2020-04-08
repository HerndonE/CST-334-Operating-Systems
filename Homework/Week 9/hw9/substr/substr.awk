# given an input file of words, output all N letter substrings
# of all words of length M or less (N must be provided on command line)
# default value of M is N+100

#
# YOUR CODE HERE
#
#!/usr/bin/awk -f
{
if(length($0) <= M)
{
for(i=1;i<=length($0);i++)
{
if(length(substr($0,i,N)) >= N)
{
print(substr($0,i,N));
}
}
}
else if(length(M)==0)
{ 
for(i=1;i<=length($0);i++)
{
if(length(substr($0,i,N)) >= N)
{
print(substr($0,i,N));
}
}
} 
else if(M < N)
{
er = "error: parameter M should be >= parameter N"
}
}

END{
if(er)
{
printf("%s", er)
}
}
