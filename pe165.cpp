// Project Euler 165 Intersections
// @date: 2018/04/13
// @author: 王珩
// 判断线段是否相交
// 给出点A(x0, y0),B(x1, y1)
// 点C(x2, y2), D(x3, y3)
// 判断线段AB与CD是否有交点，且端点不相交
// 则有cross_product(AC, AD) * cross_product(BC, BD) < 0
// && cross_product(CA, CB) * cross_product(DA, DB) < 0

#include <bits/stdc++.h>
#define limit 20000
#define MAX_N 5000
using namespace std;

// 数据结构，用来表示一个点
struct Point {
  int x, y;
  Point() {}
  Point(int x, int y) :
    x(x), y(y) {
  }
};

// 用来表示一个向量
struct Vector {
  long x, y;
  // 构造函数
  Vector(Point a, Point b) :
    x(b.x - a.x), y(b.y - a.y) {
  }
  Vector(int start, int end) :
    x(start), y(end) {
  }
  int cross_product(Vector vect) {
    return x*vect.y - vect.x*y;
  }
  Vector negative() {
    return Vector(-x, -y);
  }
};

int T[limit];
Point P[MAX_N][2];
// 函数
// 判断是否相交
bool intersection(Point a, Point b, Point c, Point d) {
  // 生成相关向量
  Vector ac = Vector(a, c);
  Vector ad = Vector(a, d);
  Vector bc = Vector(b, c);
  Vector bd = Vector(b, d);
  Vector ca = ac.negative();
  Vector cb = bc.negative();
  Vector da = ad.negative();
  Vector db = bd.negative();
  // 计算相关叉积
  return ac.cross_product(ad) * bc.cross_product(bd) < 0 &&
						   ca.cross_product(cb) * da.cross_product(db) < 0;
}

// 生成随机数
void generator_pesudo_random() {
  long s = ((long) 290797 * 290797) % 50515093;
  for (int i = 0; i < limit; i++) {
    T[i] = (int) (s % 500);
    s = (s * s) % 50515093;
    if (i < 4) {
      printf("%d\n", T[i]);
    }
  }
}

int main(int arg, char *argv[]) {
  int count = 0;
  generator_pesudo_random();
  for (int i = 0; i < limit; i+=4) {
    P[count][0] = Point(T[i], T[i+1]);
    P[count++][1] = Point(T[i+2], T[i+3]);
  }
  int res = 0;
  for (int i = 0; i < MAX_N; i++) {
    for (int j = i+1; j < MAX_N; j++) {
      if (intersection(P[i][0], P[i][1], P[j][0], P[j][1])) {
        res++;
      }
    }
  }
  printf("%d\n", res);
}
