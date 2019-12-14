#include <bits/stdc++.h>

#define max(x, y) ((x) > (y)) ? (x) : (y)
#define MAX 1000000000000000
using namespace std;

map<int, vector<long> > word_squares;	// 平方的长度和数
int char_index[26];
int digit[10];	// 用来表示末位字母
set<long> squares;
long res = 0;

// 分割字符
template<typename Out>
void split(const string &s, char delim, Out result)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		*(result++) = item;
	}
}

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}


long com_word_square(string, int, long, string);
int anagramic_sqaure(string, string);
bool is_anagramic(string, string);

int anagramic_sqaure(string word1, string word2)
{
	int word_size = word1.size();
	vector<long> sqs = word_squares[word_size];
	int sq_size = sqs.size();
	
	long ma_sq = 0;
	for (int i = 0; i < sq_size; ++i) {
		long ans = com_word_square(word1, word_size, sqs[i], word2);
		memset(char_index, -1, sizeof(char_index));
		memset(digit, -1, sizeof(digit));
		ma_sq = max(ma_sq, ans);
	}
	res = max(ma_sq, res);
}

long com_word_square(string word1, int word_size, long number, string word2)
{
	int ind;
	int i;
	int tail_number;
	long copy = number;
	for (i = word_size - 1; i >= 0; --i) {
		ind = word1[i] - 'A';
		tail_number = number % 10;
		if (char_index[ind] == -1 && digit[tail_number] == -1) {
			char_index[ind] = tail_number;
			digit[tail_number] = ind;
		}
		// 前面一个表示相同的字母对应相同的数字
		// 后面一个表示不同的字母对应不同的数字
		else if (char_index[ind] != tail_number || digit[tail_number] != ind) {
			return -1;
		}
		number /= 10;
	}

	long sq = 0;
   	
	int num = char_index[(int) (word2[0] - 'A')];
	if (num == 0) return -1;
	for (i = 0; i < word_size; ++i) {
		num = char_index[(int) (word2[i] - 'A')];
		sq *= 10;
		sq += num;
	}

	if (squares.find(sq) != squares.end()) {
		return max(copy, sq);
	}
	return -1;	
}

bool is_anagramic(string word1, string word2) 
{
	string w1 = word1;
	string w2 = word2;
	sort(w1.begin()+1, w1.end()-1);
	sort(w2.begin()+1, w2.end()-1);
	return w1 == w2;
}

long pow(long base, int expt)
{
	long res = 1;
	for (int i = 0; i < expt; ++i) {
		res *= base;
	}
	return res;
}

void generate_square()
{
	long j = 1;
	for (int i = 1; i < 15; ++i) {
		vector<long> sqs;
		for (; j*j < pow(10, i); ++j) {
			sqs.push_back(j*j);
			squares.insert(j*j);
		}
		word_squares[i] = sqs;
	}
}

int main(void)
{
	generate_square();
	printf("Have finished square\n");
	fstream file;
	string x;
	file.open("./p098_words.txt");
	file >> x;
	vector<string> words = split(x, ',');
	int max_len = 0;
	for (int i = 0; i < words.size(); ++i) {
		for (int j = i+1; j < words.size(); ++j) {
			if (is_anagramic(words[i], words[j])) {
				int length = words[i].size();
				anagramic_sqaure(words[i].substr(1, length - 2), words[j].substr(1, length - 2));
			}
		}
	}	

	printf("max square is: %ld\n", res);

}
