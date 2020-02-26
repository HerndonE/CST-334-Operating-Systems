BEGIN{
    successes = 0
    failures = 0
}

$4 ~ /returned/{
	if ($5 != -1){
	    successes += 1
	} else {
	    failures += 1
	}
    }

END {
    print("num successes: "successes"; num failures: "failures)
}
