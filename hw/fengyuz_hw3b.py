#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 26 17:56:53 2017

@author: zhao_fengyu
"""

import sys
import copy
##############################################################
## Skeleton code of dynamic programming version of changeMoney
## Arguments:
## - total : (integer) total amount of money to make
## - unit : list of containing units of bills in integer
## - stored : dictionary containing a stored information to avoid
## redundancy

def dpChangeMoney(total, units, stored):
    if str([total,units]) not in stored.keys():
        if ( abs(total) < 1e-10 ): ## exact amount within precision
            stored[str([total,units])] = [{}] ## return a solution (nothing to pay)
        elif ( total < 0 ):
            stored[str([total,units])] = [] ## no solution is total is negative
        else:
            n = len(units)
            ret = []
            for i in range(0,n): ## only use i-th or later units
                sols = dpChangeMoney(total-units[i],units[i:n],stored)
                a = copy.deepcopy(sols)
                for sol in a:
                    if ( units[i] in sol ):
                        sol[units[i]] += 1
                    else:
                        sol[units[i]] = 1
                    ret.append(sol)
            stored[str([total,units])] = ret
    return stored[str([total,units])]

dollars = int(sys.argv[1])
bills = [int(x) for x in sys.argv[2:len(sys.argv)]]
ways = dpChangeMoney(dollars, bills, {})
print("There are " + str(len(ways)) + " possible ways to make "+str(dollars))
for way in ways:
    print(sorted(way.items()))
