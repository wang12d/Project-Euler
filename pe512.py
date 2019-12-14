from time import clock
from math import sqrt

MAX = 5 * 10 ** 8

def sieve(n):
    totients = [0 for i in range(n+1)]
    totients[1] = 1
    for i in range(2, n+1):
        if not totients[i]:
            for j in range(i, n+1, i):
                if not totients[j]: totients[j] = j
                totients[j] = totients[j] // i * (i - 1)
    
    return totients

def fast_pow(base, exp, mod):
    res = 1
    while (exp):
        if exp & 1:
            res = base * res % mod
        base = base * base % mod
        exp //= 2
    return res

''' 等比数列求和取模 '''
def sum_seq(q, n, mod=MAX):
    if n == 0: return 1
    if n % 2 != 0:
        half = (n + 2) // 2
        return (1 + fast_pow(q, half, mod)) * sum_seq(q, half-1, mod) % mod
    else:
        return (1 +  q * sum_seq(q, n - 1, mod) % mod ) % mod

def run(n):
    phi = sieve(n)
    res = 0
    for i in range(1, n+1):
        res += ((i // 2 * i * phi[i] % (i + 1)) + 
                ((i // 2 + (0 if i % 2 == 0 else 1)) * phi[i] % (i+1))) % (i+1)
    return res

if __name__ == '__main__':
    start = clock()
    ans = run(1000000)
    end = clock()
    print("{}\n{:.4f}ms".format(ans, (end - start)*1000))
