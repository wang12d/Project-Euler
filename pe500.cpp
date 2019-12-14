#include <bits/stdc++.h>

using namespace std;

#define MAX_N 10000000
#define M 500500507

// 创建所需的数据结构
struct Num {
  long n;   // n = base^expt
  int base, expt;
  bool operator < (const Num &o) const {
    return n > o.n;
  }
};

priority_queue<Num> q;   // 优先队列，用来删除值
vector<int> primes;
int number[MAX_N+1];
map<int, int> m;        // 用来存储<base, exp>

void sieve()
{
    memset(number, 1, sizeof(number));
    number[0] = number[1] = 0;
    for (int i = 2; i * i <= MAX_N; ++i) {
        if (number[i]) {
	  for (int j = i*i; j <= MAX_N && j > 0; j+=i) {
	    number[j] = 0;
	  }
        }
    }
    for (int i = 0; i <= MAX_N; ++i) {
        if (number[i])
            primes.push_back(i);
    }
}

long fast_mod(long base, unsigned long exp) 
{
    long res = 1;    //初始值
    base = base % M;  // 取余，防止结果过大
    while (exp > 0) {
        // 如果是偶数则计算余数
        if (exp & 1) {
            res = (res * base) % M;
        }
        exp >>= 1;
        base = (base * base) % M;
    }
    return res;
}

// 将可能用到的数插入到优先队列中
void insert_number(int n, int p) {
  long power = n;
  power = power*power;
  int exp = 2;
  // 防止溢出
  while (p >= power && power > 0) {
    q.push(Num{power, n, exp});
    power *= power;
    exp *= 2;
  }
}
// 将全部的数据准备好
void prepare() {
  int N = 500500;
  int p = primes[N - 1];
  for (int i = 0; i < N; i++) {
    insert_number(primes[i], p);
  }
}

void init() {
  sieve();
  prepare();
  for (int i = 0; i < 500500; i++) {
    m[primes[i]] = 1;
  }
}

int main()
{
  init();
  int end_pointer = 500500 - 1;
  int final; // 指针指向的最后一个值
  Num out;  // 优先队列中被弹出的值
  while (true) {
    final = primes[end_pointer--];
    out = q.top();
    cout << final << ' ' << out.n << ' ' << out.base << ' ' << out.expt << endl;
    if (out.n >= final || q.empty()) {
      break;
    }
    q.pop();
    m[out.base] += out.expt;
    m.erase(final);
  }

  long res = 1;
  map<int, int>::iterator it;
  for (it = m.begin(); it != m.end(); ++it) {
    res = ((res % M) * fast_mod(it->first, it->second)) % M;
  }
  cout << res << endl;
}
