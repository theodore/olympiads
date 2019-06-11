#!/bin/bash -e
for ((i = 1; i <= $1; ++i))
do
	for ((j = 1; j <= $i; ++j))
	do
		echo $i $j
		echo $i $j | ./brute > ans
		echo $i $j | ./catalan > out
		diff -q ans out
	done
done
