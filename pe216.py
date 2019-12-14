from random import randrange

def miller_rabin(n, num_trials=4):
    """
    True if n is likely prime, and False if n 
    is definitely not prime.  
    """
    if n in [2,3]: return True
    if n <= 4: return False
    m = n - 1
    k = 0
    while m%2 == 0:
        k += 1; m /= 2
    # Now n - 1 = (2**k) * m with m odd
    for i in range(num_trials):
        a = randrange(2,n-1)                  
        apow = pow(a, m, n)
        if apow==1 or apow==n-1:
            continue #no witness for compositeness
        some_minus_one = False
        for r in range(k-1):             
            apow = (apow*apow)%n
            if apow == n-1:
                some_minus_one = True #no witness for compositeness
                break
        if not some_minus_one: return False 
    return True

if __name__ == '__main__':
    n = int(input())
    res = 0
    for i in range(2, n):
        v = 2*i*i - 1
        if (miller_rabin(v)):
            res += 1
            # print("i = {}, v = {}".format(i, v))

    print("{}".format(res))
