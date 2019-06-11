#!/bin/bash -e
for (( i = 0; i < $1; ++i ))
do
	echo $i
	echo $2 $3 $RAMDOM | ./data > "in"
	./MTREE < "in" > "out"
	./brute < "in" > "ans"
	diff ans out
done
