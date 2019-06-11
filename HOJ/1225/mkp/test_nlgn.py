#!/usr/bin/env python
from os import system

system('rm res')

def go(n, x):
    print x
    system('echo -n -e ' + x + ' : >> res')
    system('/usr/bin/time -f %e -o res -a bash -c \'echo ' + str(n) + ' | ./' + x + '\'')

for i in range(1, 10):
    print 'i =', i
    system('echo %d: >> res' %i)
    go(10**i, 'nlgn_arr')
    go(10**i, 'nlgn_bit')
    go(10**i, 'nlgn_man')
    system('echo >> res')
