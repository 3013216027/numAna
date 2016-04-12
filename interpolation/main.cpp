/* **********************************************

  File Name: main.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Tue Mar 29 17:00:31 2016

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "interpolation.cpp"
using namespace inter;

int main() {
	CubicInter* a = new CubicInter();
	a->push(27.7, 4.1)
		->push(28, 4.3)
		->push(29, 4.1)
		->push(30, 3.0)
		->set(CubicInter::CONDITION::FIRST, 3.0, -4.0)
		->print();
	delete a;
	return 0;
}
