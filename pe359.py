import time
from math import sqrt, ceil, floor


def floor_number(f, r):
    if f == 1:
        return r * (r + 1) // 2
    k = f - 2
    if f % 2 == 0:
        k += 1
    n =  r // 2
    if r % 2 == 1:
        n += 1
        init = f * f // 2
        return (2 * n + 2 * k + 1) * (n - 1) + init
    else:
        init = 0
        if f % 2 == 0:
            init = (f+1) * (f+1) - f * f // 2
        else:
            init = f * f - f * f // 2
        return (r + 2 * k + 3) * (n - 1) + int(init)


def factor_number(n):
    return [i for i in range(1, ceil(sqrt(n))) if n % i == 0]

if __name__ == "__main__":
    time_begin = time.time()
    n = 71328803586048
    factors = factor_number(n)
    res = 0
    for i in factors:
        res += floor_number(i, n // i) + floor_number(n // i, i)
    
    print(floor_number(1, 1))
    print(floor_number(1, 2))
    print(floor_number(2, 1))
    print(floor_number(10, 20))
    print(floor_number(25, 75))
    print(floor_number(99, 100))
    print(res % (100000000))
    print("Time cost: {:.3f}s".format(time.time()-time_begin))