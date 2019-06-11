#!/bin/bash -e
for ((i = 0; i < $1; ++i ))
do
	echo $RANDOM $2 $3 | ./data
	#cat in
	./1552
	./brute
	diff ans out
done
