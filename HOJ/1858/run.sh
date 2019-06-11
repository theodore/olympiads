#!/bin/bash -e
for (( i = 0; i < $1; ++i ))
do
	echo $i
	echo $RANDOM $2 $3 | ./data
	./1858 < in > ans
	./zkw < in > out
	diff -q ans out
done
