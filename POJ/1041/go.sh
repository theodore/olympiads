#!/bin/bash -e
for (( i = 0; i < $1; ++i ))
do
	echo $i
	echo $2 $2 $3 $RANDOM | ./data > "in"
	./trip < "in" > "out"
done
