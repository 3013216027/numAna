/* **********************************************

  File Name: e1_20.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed 20 Apr 2016 09:01:16 PM CST

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "../interpolation.h"
using namespace inter;

int main() {
	CubicInter* p = new CubicInter();
	
	//add points
	p->push(0.25, 0.5)->push(0.3, 0.5477)->push(0.39, 0.6245)
		->push(0.45, 0.6708)->push(0.53, 0.7280);
	
	//first condition
	cout << "solve (1): " << endl;
	p->set(CubicInter::CONDITION::FIRST, 1, 0.6868)->print();

	//second condition
	cout << "solve (2): " << endl;
	p->set(CubicInter::CONDITION::SECOND, 0, 0)->print();

	delete p;
	
	system("pause");
	return 0;
}
