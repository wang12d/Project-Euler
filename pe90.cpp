#include <bits/stdc++.h>

#define SIZE 6
using namespace std;

bool squares[100];	// 用来存储是否组成小于100的平方
vector<vector<int> > all_combs;
vector<int> combinations;
int chance[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

bool is_suitable(vector<int> die1, vector<int> die2)
{
	int i, j;
	int ro1, ro2;
	int cnt = 0;
	for (i = 0; i < SIZE; ++i) {
		ro1 = die1[i];
		for (j = 0; j < SIZE; ++j) {
			ro2 = die2[j];
			squares[ro1*10 + ro2] = true;
			squares[ro2*10 + ro1] = true;

			if (ro1 == 6 || ro1 == 9) {
				squares[(ro1 == 6 ? 90 + ro2 : 60 + ro2)] = true;
				squares[(ro1 == 6 ? ro2*10+9 : ro2*10+6)] = true;
			}
			
			if (ro2 == 6 || ro2 == 9) {
				squares[(ro2 == 6 ? 90 + ro1 : 60 + ro1)] = true;
				squares[(ro2 == 6 ? 10 * ro1 + 9 : 10 * ro1 + 6)] = true;
			}
			
					
		}
	}
	
	for (i = 1; i < 10; ++i) {
		if (squares[i*i]) {
			cnt++;
		}
	}

	memset(squares, false, sizeof(squares));
	
	return cnt == 9;	
}

void find_combs(int offset, int ind)
{
	if (ind == 0) {
		all_combs.push_back(combinations);
		return;
	}
	
	for (int i = offset; i <= 10 - ind; ++i) {
		combinations.push_back(chance[i]);
		find_combs(i+1, ind-1);
		combinations.pop_back();
	}
}

void solver()
{
	int res, size, i, j;
	find_combs(0, 6);
	
	res = 0;
	size = all_combs.size();
	cout << "All the possible conditions is: " << size << endl;
	for (i = 0; i < size; ++i) {
	   for (j = i; j < size; ++j) {
		if (is_suitable(all_combs[i], all_combs[j])) {
			++res;
		}
	   }
	}

	cout << res << endl;
}

int main()
{
	solver();
}
