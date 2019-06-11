#!/bin/bash -e
for (( i = 0; i < $1; ++i )); do
	./rectbarn_data
	./rectbarn
	./rectbarn_brute
	diff rectbarn.ans rectbarn.out
done;
