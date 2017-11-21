import sys; ## to use sys.argv
def changeMoney(total, units):
    if ( abs(total) < 1e-10 ): ## exact amount within precision
        return [{}] ## return a solution (nothing to pay)
    elif ( total < 0 ):
        return [] ## no solution is total is negative
    else:
        n = len(units)
        ret = []
        for i in range(0,n): ## only use i-th or later units
            sols = changeMoney(total-units[i],units[i:n])
            for sol in sols:
                if ( units[i] in sol ):
                    sol[units[i]] += 1
                else:
                    sol[units[i]] = 1
                ret.append(sol)
        return ret
dollars = float(sys.argv[1]) ## get input arguments
bills = [float(x) for x in sys.argv[2:len(sys.argv)]] ## convert to float
ways = changeMoney(dollars, bills)
print("There are " + str(len(ways)) + " possible ways to make"+str(dollars)) ## print total number of solution
for way in ways:
    print(way)