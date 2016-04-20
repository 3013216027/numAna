/* **********************************************

  File Name: main.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed 20 Apr 2016 02:32:05 PM CST

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "../../interpolation.h"
using namespace inter;

NewtonInter* read_dot(NewtonInter* p, const char* file_name) {
	assert(p != NULL);

	FILE* fin = fopen(file_name, "r");
	assert(fin != NULL);

	while (fgetc(fin) != '\n'); //ignore the header line

	pair<double, double> pin;
	while (fscanf(fin, "%lf, %lf", &pin.first, &pin.second) != EOF) {
		p->push(pin);
	}

	fclose(fin);
	
	return p;
}

int main() {
	NewtonInter* test1 = new NewtonInter;
	double tag1 = 0.596;

	read_dot(test1, "case1.dot")->print();
	fprintf(stdout, "f(%f)= %.5f\n", tag1, test1->get(tag1));

	delete test1;

	return 0;
}
