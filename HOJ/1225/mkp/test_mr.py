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
    go(10**i, 'next_p')
    system('echo >> res')
