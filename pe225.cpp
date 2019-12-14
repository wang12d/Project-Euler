/**
 * Project Euler 225 Tribonacci non-divisors
 * The sequence 1, 1, 1, 3, 5, 9, 17, 31, 57, 105, 193, 355, 653, 1201 ...
 * is defined by T1 = T2 = T3 = 1 and Tn = Tn-1 + Tn-2 + Tn-3.
 * It can be shown that 27 does not divide any terms of this sequence.
 * In fact, 27 is the first odd number with this property.
 * Find the 124th odd number that does not divide any terms of the above sequence.
 * 
 * Solutions: From the modulo arithmetic, we kown that if (n + m) % y == (n % y + m % y) % y.
 * Thus, from the tribonacci sequence we have n1 % m + n2 % m + n3 % m == n4 % m
 * if the three consecutive reapted, then the whole sequence % m reapted.
 * Therefore, m is a non-divisor of tribonacci sequence
 **/

#include <iostream>
#include <sstream>

using namespace std;

// Fuctions

// if m a non-divisor of tribonacci sequence?
bool is_non_divisor(int m);


bool is_non_divisor(int m)
{
  int a = 1, b = 1 , c = 1 % m;
  int d;   // the 4th term
  while (true)
  {
    d = (a + b + c) % m;
    if (d == 0)
    {
      return false;
    }
    a = b;
    b = c;
    c = d;
    if (a == 1 && b == 1 && c == 1)
    {
	return true;
    }
  }
}

// Unit test
int main(int argc, char *argv[])
{
  int m = 1;  // the initiation odd number
  istringstream ss(argv[1]);
  int n;
  ss >> n;
  while (n)
  {
    if (is_non_divisor(m))
    {
      n--;
    }
    if (n)
    {
      m += 2;
    }
  }
  cout << m << endl;
}
