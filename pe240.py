from itertools import combinations, permutations

CACHE = dict()
def partition_into_k_parts(n: int, k: int, l: int = 1):
    if k < 1:
        raise StopIteration
    if k == 1:
        if n >= l:
            yield (n,)
        raise StopIteration
    for i in range(l, n+1):
        for result in partition_into_k_parts(n-i, k-1, i):
            yield (i,) + result

def aggregate(k: int, n: int=10) -> set:
    """
    Given n, find the number of ways to roll k dices
    """
    if (k in CACHE):   
        return CACHE[k]
    result = set()
    for i in range(1, k+1):
        partition_list = list(partition_into_k_parts(n, i))
        comb_index = list(permutations(range(k), i))
        for each_partition in partition_list:
            for comb in comb_index:
                tmp = [0]*(k+1)
                for (u, v) in zip(comb, each_partition):
                    tmp[u+1] = v
                result.add(tuple(tmp))
    CACHE[k] = result 
    return result
        
if __name__ == '__main__':
    import math
    import time
    number_of_dice = 20
    max_roll_value = 12
    number_of_top_needed = 10
    sum_needed = 70
    timer = time.perf_counter()
    partition_yields = partition_into_k_parts(sum_needed, number_of_top_needed)
    result = 0
    for i in partition_yields:
        max_value = max(i)
        if max_value <= max_roll_value:
            count = [0]*(max_roll_value+1)
            for j in i:
                count[j] += 1
            k = min(i)
            aggregate_value = aggregate(k, number_of_dice - number_of_top_needed)
            for all_possible_ways in aggregate_value:
                for j in range(1, k+1):
                    count[j] += all_possible_ways[j]
                max_ways = math.factorial(number_of_dice)
                for j in count:
                    max_ways //= math.factorial(j)
                result += max_ways
                for j in range(1, k+1):
                    count[j] -= all_possible_ways[j]
    
    print("{0:3f}ms".format((time.perf_counter() - timer)*10**3)) 
    print(result)
