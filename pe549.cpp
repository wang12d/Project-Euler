#include <bits/stdc++.h>
#define MAX_N 100000000

using namespace std;
// define fuction
void get_prime_nth(int p);    // 用来计算p^n，直到p^n > MAX_N
void sieve();                // 用来产生1~limit的素数
int get_smallest_factorial(int n);      // compute the smallest m that m! % n == 0
// ****************************************

// ****************************************
// data
vector<int> primes;         // primes
map<int, int> cache;       // store the minmum m! % p
int number[MAX_N + 1];
// ****************************************
void sieve() {
  memset(number, 1, sizeof(number));

  number[0] = number[1] = 0;
  // sieve generate primes
  for (int i = 2; i*i <= MAX_N; i++) {
    // if i is primes, then i*n is not prime
    if (number[i]) {
      for (int j = i*i; j <= MAX_N; j += i) {
	// in case of overflow
	if (j < 0) break;
	number[j] = 0;
      }
    }
  }

  // add the primes into set
  for (int i = 2; i <= MAX_N; i++) {
    if (number[i]) {
      primes.push_back(i);
    }
  }
}

void get_prime_nth(int p) {
  long power = p; // the number of current power of p^n
  int result;    // the smallest m
  long factorial;
  for (int exp = 1; power <= MAX_N; exp++) {
     result = p;  // the smallest should be the mupliter of prime
     factorial = p; // the muplie of prime
     while (factorial % power != 0) {
       result = result + p;
       factorial = factorial * result;
     }
     cache[power] = result;
     power = power * p;
  }
}

int get_smallest_factorial(int n) {
  int ans = 1;
  if (number[n]) {
    return n;
  }
  for (int p: primes) {
    // if n % p != 0, continue
    if (n % p != 0) {
      continue;
    }
    // factor the n
    int power = 1;
    while (n % p == 0) {
      power = power * p;
      n = n / p;
    }

    ans = max(ans, cache[power]);
    if (n == 1) {
      return ans;
    }
    // if n is prime
    if (number[n]) {
      return max(ans, n);
    }
  }
  return ans;
}

int main(int arg, char *argv[]) {
  sieve();    // generator primes
  printf("Sieve done\n");
  // fill the cache
  for (int p: primes) {
    get_prime_nth(p);
  }
  printf("Prime progression done\n");
  long res = 0;
  for (int i = 2; i <= MAX_N; i++) {
    int m = get_smallest_factorial(i);
    res = res + m;
  }
  printf("%ld\n", res);
}
