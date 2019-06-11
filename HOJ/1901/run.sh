#!/bin/bash -e
for (( i = 0; i < $1; ++i ))
do
	echo "Test case #$i"
	echo $RANDOM $2 $3 $4 | ./data
	./brute < in > ans
	./ranking < in > out
	diff ans out
done
