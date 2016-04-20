/* **********************************************

  File Name: cubic.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Tue Mar 29 17:00:31 2016

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "../../interpolation.h"

using namespace inter;

CubicInter* read_dot(CubicInter* p, const char* file_name) {
	assert(p != NULL);

	FILE* fin = fopen(file_name, "r");
	assert (fin != NULL);

	while (fgetc(fin) != '\n'); //ignore first line, which is table header
	
	//readin the final condition
	pair<double, double> ending;
	fscanf(fin, "%lf, %lf", &ending.first, &ending.second);
	
	//readin the rest data(points)
	pair<double, double> pin;
	while (fscanf(fin, "%lf, %lf", &pin.first, &pin.second) != EOF) {
		p->push(pin);
	}

	return p->set(CubicInter::CONDITION::FIRST, ending.first, ending.second);
	//or: return p;
}

int main() {
	CubicInter* test1 = new CubicInter();
	read_dot(test1, "cubic1.dot");
	test1->print();
	
	CubicInter* test2 = new CubicInter();
	read_dot(test2, "cubic2.dot");
	test1->print();
	
	delete test1;
	delete test2;
	
	return 0;
}
