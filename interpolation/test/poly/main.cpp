/* **********************************************

  File Name: main.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed 20 Apr 2016 08:43:34 PM CST

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "../../interpolation.h"
using namespace inter;

int main() {
	Poly* p = new Poly();
	double x, y;
	while (cin >> x >> y) {
		p->push(x, y);
	}
	p->print();
	delete p;
	return 0;
}
