#!/bin/bash -e
for (( i = 0; i < $1; ++i ))
do
	echo "test case #$i"
	echo $RANDOM $2 $3 $4 | ./data
	./spfa
	./rabbit < "in" > "out"
	diff ans out
done
