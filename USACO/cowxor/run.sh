#!/bin/bash -e
echo $1 | ./cowxor_data
./cowxor
./cowxor_brute
diff cowxor.ans cowxor.out
