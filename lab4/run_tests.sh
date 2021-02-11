#!/bin/bash

test_list=(tests/input*.txt)

for i in "${!test_list[@]}"; 
	do
		echo "Test №$((i + 1))"
		./exe/result <"${test_list[$i]}" >"tests/output$((i + 1)).txt"
	if	cmp -s "tests/expect-out$((i + 1)).txt" "tests/output$((i + 1)).txt"; 
		then
		echo "PASSED"
	else
		echo "FAILED"
		break		
	fi
done
		
		
