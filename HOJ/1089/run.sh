#!/bin/bash
for (( n = 0; n <= 32; ++n ))
do
	for (( d = 0; d <= 16; ++d ))
	do
		echo $n $d | ./std
		echo $n $d | ./n-tree
		if diff ans out
		then
			echo n = $n
			echo d = $d
			echo $n $d >> in
		fi
	done
done
