/* **********************************************

  File Name: p1.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed 20 Apr 2016 09:11:19 PM CST

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "../interpolation.h"
using namespace inter;

vector<double> xs;

void read_x_rays() {
	double x;
	while (cin >> x) {
		xs.push_back(x);
	}
}

int main() {
	read_x_rays(); //readin data

	CubicInter* ci = new CubicInter();
	NewtonInter* ni = new NewtonInter();
	
	//add points
	ci->push(0.2, 0.98)->push(0.4, 0.92)->push(0.6, 0.81)->push(0.8, 0.64)->push(1.0, 0.38);
	ni->push(0.2, 0.98)->push(0.4, 0.92)->push(0.6, 0.81)->push(0.8, 0.64)->push(1.0, 0.38);
	

	//Newton Interpolation
	cout << "Newton Interpolation: " << endl;
	ni->print();
	for (int i = 0; i < (int)xs.size(); ++i) {
		fprintf(stdout, "P[4](%.5f) = %.5f\n", xs[i], ni->get(xs[i]));
	}
	fprintf(stdout, "--------------------------------------------\n");

	//Cubic Interpolation
	cout << "Cubic Interpolation: " << endl;
	ci->set(CubicInter::CONDITION::FIRST, 0, 0)->print(); //natural condition o_O
	for (int i = 0; i < (int)xs.size(); ++i) {
		fprintf(stdout, "S(%.5f) = %.5f\n", xs[i], ci->get(xs[i]));
	}
	
	//free memory :lol:
	delete ci;
	delete ni;

	return 0;
}
