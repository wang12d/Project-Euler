/**
 * Project Euler Problem 196
 * @author: Heng
 * @Date: 2018/08/27
 * @Modified: 2018/08/27
 * using the sieve to shift all the non-prime
 **/

#include "pe_algs.h"
#include <iostream>
#define MAX 30000000

/*
    find the triple of triangle
*/

bool numbers[MAX];
bool triple[MAX];

// find min mutiple of p between low and high
long bin_search(int p, long ptr, long base)
{
    long lo = 1, hi = (ptr + base) / p;
    long mid;
    while (hi >= lo) {
        mid = (lo + hi) / 2;
        if (mid * p >= base) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    return lo*p - base;
}


void triangle(long level, long base)
{
    long val = (level - 1) * level / 2 + 1;
    long current_end = val + level - 1;
    int p_count;
    if (numbers[val - base]) {
        p_count = 0;
        numbers[val - level + 1 - base] ? ++p_count : p_count; // up
        numbers[val - level + 2 - base] ? ++p_count : p_count; // up right
        numbers[val + 1 - base] ? ++p_count : p_count; // right
        numbers[val + level - base] ? ++p_count : p_count; // down
        numbers[val + level + 1 - base] ? ++p_count : p_count; // down right
        if (p_count > 1) {
            triple[val - base] = 1;
        }
    }

    long tmp = val + 1;
    for (; tmp <= current_end - 2; ++tmp) {
        if (numbers[tmp - base]) {
            p_count = 0;
            numbers[tmp - level+1 - base] ? ++p_count : p_count; // up
            numbers[tmp - level - base] ? ++p_count : p_count;     // up_left
            numbers[tmp - level+2 - base] ? ++p_count : p_count; // up_right
            numbers[tmp - 1 - base] ? ++p_count : p_count;   // left
            numbers[tmp + 1 - base] ? ++p_count : p_count;   // right
            numbers[tmp + level - base] ? ++p_count : p_count; // down
            numbers[tmp + level - 1 - base] ? ++p_count : p_count; // down left
            numbers[tmp + level + 1 - base] ? ++p_count : p_count;  // down right
            if (p_count > 1) {
                triple[tmp - base] = 1;
            }
        }
    }

    // second to last val
    if (numbers[tmp - base]) {
        p_count = 0;
        numbers[tmp - level + 1 - base] ? ++p_count : p_count; // up
        numbers[tmp - level - base] ? ++p_count : p_count; // up_left
        numbers[tmp - 1 - base] ? ++p_count : p_count;   // left
        numbers[tmp + 1 - base] ? ++p_count : p_count;   // right
        numbers[tmp + level - base] ? ++p_count : p_count; // down
        numbers[tmp + level - 1 - base] ? ++p_count : p_count; // down left
        numbers[tmp + level + 1 - base] ? ++p_count : p_count;  // down right
        if (p_count > 1) {
            triple[tmp - base] = 1;
        }
    }
    ++tmp;

    // last val
    if (numbers[tmp - base]) {
        p_count = 0;
        numbers[tmp - level - base] ? ++p_count : p_count; // up_left
        numbers[tmp - 1 - base] ? ++p_count : p_count;   // left
        numbers[tmp + level - base] ? ++p_count : p_count; // down
        numbers[tmp + level - 1 - base] ? ++p_count : p_count; // down left
        numbers[tmp + level + 1 - base] ? ++p_count : p_count;  // down right
        if (p_count > 1) {
            triple[tmp - base] = 1;
        }
    }

}

/* 
    using sieve to find primes of the triple level
*/

long find_triple_prime(long level)
{
    // get the max prime
    std::vector<int> primes = sieve(level+1);

    long min_val = (level- 3) * (level - 2) / 2 + 1;
    long max_val = (level + 2) * (level + 3) / 2;
    long base = min_val;
    long offset = max_val - base;
    long val = (level - 1) * level / 2 + 1;
    long current_end = val + level - 1;

    for (long i = 0; i < offset; ++i) {
        numbers[i] = 1;
    }

    std::cout << "all done." << std::endl;
    std::vector<int>::iterator end_vec = primes.end();

    for (std::vector<int>::iterator i = primes.begin(); i != end_vec; ++i) {
        long ptr = bin_search(*i, offset, base);
        for (long v = ptr; v < offset; v += (*i)) {
            numbers[v] = 0;
        }
    }

    triangle(level-1, base); triangle(level+1, base);
    long res = 0;
    // first val
    int p_count;
    if (numbers[val - base]) {
        p_count = 0;
        numbers[val - level + 1 - base] ? ++p_count : p_count; // up
        numbers[val - level + 2 - base] ? ++p_count : p_count; // up right
        numbers[val + 1 - base] ? ++p_count : p_count; // right
        numbers[val + level - base] ? ++p_count : p_count; // down
        numbers[val + level + 1 - base] ? ++p_count : p_count; // down right
        if (p_count > 1 || triple[val-level + 1 - base] || triple[val-level+2 - base]
        || triple[val+level - base] || triple[val+level+1 - base]) {
            res += val;
        }
    }

    long tmp = val + 1;
    for (; tmp <= current_end - 2; ++tmp) {
        if (numbers[tmp - base]) {
            p_count = 0;
            numbers[tmp-level+1 - base] ? ++p_count : p_count; // up
            numbers[tmp-level - base] ? ++p_count : p_count;     // up_left
            numbers[tmp-level+2 - base] ? ++p_count : p_count; // up_right
            numbers[tmp-1 - base] ? ++p_count : p_count;   // left
            numbers[tmp+1 - base] ? ++p_count : p_count;   // right
            numbers[tmp+level - base] ? ++p_count : p_count; // down
            numbers[tmp+level-1 - base] ? ++p_count : p_count; // down left
            numbers[tmp+level+1 - base] ? ++p_count : p_count;  // down right
            if (p_count > 1 || triple[tmp-level+1 - base] || triple[tmp-level+2 - base]
            ||  triple[tmp+level-1 - base] || triple[tmp+level+1 - base] || triple[tmp+level - base] || triple[tmp-level - base]) {
                res += tmp;
            }
        }
    }

    if (numbers[tmp - base]) {
        std::cout << tmp << std::endl;
        p_count = 0;
        numbers[tmp-level+1 - base] ? ++p_count : p_count; // up
        numbers[tmp-level - base] ? ++p_count : p_count; // up_left
        numbers[tmp-1 - base] ? ++p_count : p_count;   // left
        numbers[tmp+1 - base] ? ++p_count : p_count;   // right
        numbers[tmp+level - base] ? ++p_count : p_count; // down
        numbers[tmp+level-1 - base] ? ++p_count : p_count; // down left
        numbers[tmp+level+1 - base] ? ++p_count : p_count;  // down right
        if (p_count > 1 || triple[tmp-level+1 - base] || triple[tmp+level-1 - base] || 
            triple[tmp+level+1 - base] || triple[tmp+level - base] || triple[tmp-level - base]) {
            res += tmp;
        }
    }
    ++tmp;

    // last val
    if (numbers[tmp - base]) {
        p_count = 0;
        numbers[tmp-level - base] ? ++p_count : p_count; // up_left
        numbers[tmp-1 - base] ? ++p_count : p_count;   // left
        numbers[tmp+level - base] ? ++p_count : p_count; // down
        numbers[tmp+level-1 - base] ? ++p_count : p_count; // down left
        numbers[tmp+level+1 - base] ? ++p_count : p_count;  // down right
        if (p_count > 1 || triple[tmp+level-1 - base] || triple[tmp+level+1 - base] || triple[tmp+level - base] || triple[tmp-level - base]) {
            res += tmp;
        }
    }

    return res;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Input error." << std::endl;
        return 0;
    }

    long n;
    long res = 0;
    for (int i = 1; i < argc; ++i) {
        sscanf(argv[i], "%ld", &n); 
        res += find_triple_prime(n);
        for (int j = 0; j < MAX; ++j) {
            numbers[j] = triple[j] = 0;
        }
    }

    std::cout << res << std::endl;
}