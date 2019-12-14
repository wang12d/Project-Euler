/**
 * Project Euler 491 Double pandigital number divisible by 11
 * @author：王珩
 * @date：2018/5/12
 *
 * 解题思路：能够被11整除的数其交替数字之和（+-+-...)也能够被11整除。
 *			 因此，又90（全部数字之和）- 2×P（正数部分）（mod 11）= 0。
 *			 经推算，符合条件的P为34, 56, 23, 67, 45。
 **/

#include <set>
#include <vector>
#include <stdio.h>
#include <cstring>
#define FACT 362880
#define FACTT 3628800

using namespace std;

unsigned long ans;
long facts[] = {0, 0, 0, 0, 0, 0, 0, 0, 40320, 362880, 3628800};
vector<int> numbers = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5,
				6, 6, 7, 7, 8, 8, 9, 9};

vector<int> combs;
set<vector<int> > all_number_combs;

int count_zeros(const vector<int>& v) {
	int c = 0;
	for (int i = 0; i < 10; ++i) {
		if (v[i] == 0) {
			++c;
		}
	}	
	return c;
}

int count_dup(const vector<int>& v) {
	int c = 0;
	bool is_appear[10];
	memset(is_appear, false, sizeof(is_appear));

	for (int i = 0; i < 10; ++i) {
		int n = v[i];
		if (is_appear[n]) {
			++c;
		}
		else {
			is_appear[n] = true;
		}
	}
	return c;
}

int non_dup(const vector<int>& v)
{
	int c = 0;
	bool is_appear[10];
	memset(is_appear, true, sizeof(is_appear));

	for (int i = 0; i < 10; ++i) {
		int n = v[i];
		if (is_appear[n]) {
			is_appear[n] = false;
		}
		else {
			is_appear[n] = true;
		}
	}

	for (int i = 1; i < 10; ++i) {
		if (!is_appear[i]) {
			c++;
		}
	} 
	return c;
}

long pow_2(int times)
{
	long base = 1;
	while (times--) {
		base *= 2;
	}
	return base;
}

long compute_ways(int number_zeros, int number_repeats, int number_unique)
{
	long repeats = pow_2(number_repeats);
	long negative = FACTT / repeats;
	long postive = 0;
	postive += number_unique * FACT / repeats;
	postive += 2 * (number_repeats - number_zeros / 2) * FACT / repeats;
	return negative * postive;

}

/* 找出所有符合条件的P的数字组成部分 */

void show_vect(const vector<int>& vect)
{
	printf("[");
	int sum = 0;
	int size = vect.size();
	for (int i = 0; i < size; ++i) {
		printf("%d%s", vect[i], i == size-1 ? "" : " ");
		sum += vect[i];
	}
	printf("] sum=%d\n", sum);
}

void search(int ind, int k, int sum, int size)
{
	if (k == 0) {
		if (sum == 34 || sum == 56 || sum == 23 || sum == 67 || sum == 45) {
			all_number_combs.insert(combs);
		}
		return;
	}


	for (int i = ind; i <= size-k; ++i) {
		int num = numbers[i];
		combs.push_back(num);
		sum += num;
		search(i+1, k-1, sum, size);
		combs.pop_back();
		sum -= num;
	}
}

void solver()
{
	int size = numbers.size();
    search(0, 10, 0, size);

	int number_zeros, number_repeats, number_unique;
	long ways;
	
	set<vector<int> >::iterator end = all_number_combs.end();
	for (set<vector<int> >::iterator it = all_number_combs.begin(); it != end; ++it) {
		number_zeros = count_zeros(*it);
		number_repeats = count_dup(*it);
		number_unique = non_dup(*it);
		ways = compute_ways(number_zeros, number_repeats, number_unique);
		ans += ways;
	}
	printf("%ld\n", ans);
}

int main()
{
	solver();
}
