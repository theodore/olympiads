#!/usr/bin/env python
from math import *
n = int(raw_input())
g = int(raw_input())
p = 999911659
ans = 0
for i in range(1, n + 1):
    if n % i == 0:
	ans += factorial(n) / factorial(i) / factorial(n - i)
	ans %= p - 1
print g ** ans % p
