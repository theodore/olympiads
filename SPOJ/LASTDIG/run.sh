#!/bin/bash -e
for (( i = 0; i < 100; ++i )); do
	echo case $i
	./LASTDIG_data
	./LASTDIG
	./LASTDIG_brute
done;
diff answer output
