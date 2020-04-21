#!/usr/bin/awk -f
# for *every* problem ID in input, give number of incorrect (non-0) answers

# YOUR CODE HERE
BEGIN { 
FS=","
OFS=","
}
{
    if (NR != 1){
	found = 0
	for (item in problems){
	    if ($2 == item){
		found = 1
	    }
	}
	if (found == 0){
	    problems[$2] = 0
	}
	if ($3 != "0") {
	    problems[$2]++
	}
    }
}
END {
    print "prob_id,num_missed"
    num = asorti(problems, indices)
    for (i=1; i<=num; i++)
	print indices[i]","problems[indices[i]]
}
