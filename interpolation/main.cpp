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
	/*
	a->push(0.25, 0.5000)
		->push(0.30, 0.5477)
		->push(0.39, 0.6708)
		->push(0.45, 0.6708)
		->push(0.53, 0.7280)
		->set(CubicInter::CONDITION::FIRST, 1.0000, 0.6868)
		->print();
		*/
	/*
	a->push(27.7, 4.1)
		->push(28, 4.3)
		->push(29, 4.1)
		->push(30, 3.0)
		->set(CubicInter::CONDITION::FIRST, 3.0, -4.0)
		->print();
	*/
	NewtonInter* b = new NewtonInter();
	double x = b->push(0.4, 0.41075)->push(0.55, 0.57815)->push(0.65, 0.69675)
		->push(0.8, 0.88811)->push(0.9, 1.02652)->print()
		->get(0.596);
	cout << x << endl;
	delete a;
	delete b;
	return 0;
}
