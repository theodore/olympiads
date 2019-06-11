#!/usr/bin/env python
from math import *

P = 10 ** 9 - 401

def calc(n, d):
    return factorial(n) / factorial(d) ** (n / d) / factorial(n / d) % (P - 1)

def main(n):
    ans = 1
    for i in range(1, n):
	if n % i == 0:
	    ans += calc(n, i)
	    ans %= (P - 1)
    print ans

main(28)
