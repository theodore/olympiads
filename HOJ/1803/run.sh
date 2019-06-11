#!/bin/bash -e
for (( i = 0; i < $1; ++i ))
do
	echo "Test case #$i"
	echo $RANDOM $2 $3 | ./data2
	./brute < "in" > "ans"
	./query < "in" > "out"
	diff ans out
done
