#include <bits/stdc++.h>
#define A 65
using namespace std;

vector<string> strings;
int N, M; 
void rotate(string &s, int ind, int first) 
{ 
	reverse(s.begin() + ind, s.end()); 
	reverse(s.begin() + first , s.end()); 
} 
int solve(string s) 
{
   	int cnt = 0; 
	int ind; 
	int len = s.length(); 
	int last_len = len - 1, se_last_len = len - 2; 

	for (int i = 0; i < len; ++i) { 
		ind = i; 
		if (s.at(i) != A+i) { 
			if (i == se_last_len) { 
				swap(s[i], s[last_len]); 
				cnt++; return cnt; 
			} 
			while (s[++ind] != A+i); rotate(s, ind, i);
			cnt += 2;
			if (ind == last_len) --cnt;
		}
	}

	return cnt;
}

int main(int argc, char **argv)
{
	sscanf(argv[1], "%d", &N);
	sscanf(argv[2], "%d", &M);
	string s = {};
	for (int i = 0; i < N; ++i) {
		s += (A + i);
	}

	int max_len = 2*(N - 2) + 1;
	do {
		int cnt = solve(s);	
		if (cnt ==  max_len) strings.push_back(s);
	} while (next_permutation(s.begin(), s.end()));

	sort(strings.begin(), strings.end());

	cout << strings[M-1] << endl;
}
