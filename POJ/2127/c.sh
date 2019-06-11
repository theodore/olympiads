#!/bin/bash -e
for ((i = 0; i < $1; ++i))
do
	echo $2 $3 $4 $RANDOM | ./data > in
	./go < in > out
	./ch out < in
	cat out
done
