#!/bin/bash -e
for ((i = 1; ; ++i))
do
	echo $i
	echo 1 $i | ./brute > ans
	echo 1 $i | ./try > out
	diff -q ans out
done
