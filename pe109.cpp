#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

map<string, int> socres;	// 用来存储每个区域的得分情况
map<int, int> possible_condition;	// 两次投投掷飞镖可能的得分
vector<string> cards;
vector<int> double_out;

void init(void)
{
	string S = "S", D = "D", T = "T";
	string one;
	string two;
	string three;

	for (int i = 1; i <= 20; ++i) {
		one = S + to_string(i);
		two = D + to_string(i);
		three = T + to_string(i);
		
		cards.push_back(one);
		cards.push_back(two);
		cards.push_back(three);
		
		double_out.push_back(i * 2);

		socres[one] = i;
		socres[two] = 2*i;
		socres[three] = 3*i;
	}

	socres["S25"] = 25;
	socres["D25"] = 50;
	cards.push_back("S25");
	cards.push_back("D25");
	double_out.push_back(50);
}

void is_exsit(int s)
{
	if (possible_condition.find(s) == possible_condition.end()) {
		possible_condition[s] = 1;
	}
	else {
		possible_condition[s]++;
	}
}

void generate_all_possible(void)
{
	vector<string>::iterator i;
	vector<string>::iterator j;
	for (i = cards.begin(); i != cards.end(); ++i) {
		int so = socres[*i];
		is_exsit(so);
	   for (j = i; j != cards.end(); ++j) {
		   is_exsit(so  + socres[*j]);
	   }
	}
	possible_condition[0] = 1;
}


int solver(int s)
{
	vector<int>::iterator it;
	int ways = 0;
	for (it = double_out.begin(); it != double_out.end(); ++it) {
		if (*it > s) {
			break;
		}
		ways += possible_condition[s - *it];
	}

	return ways;	
}

void prepare_all(void)
{
	init();
	generate_all_possible();
}

int main(int argc, char **argv)
{
	prepare_all();
	int res = 0;
	for (int i = 2; i <= 99; ++i) {
		res += solver(i);
	}

	printf("%d\n", res);
}
