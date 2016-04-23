/* **********************************************

  File Name: p3.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed 20 Apr 2016 09:39:42 PM CST

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "../interpolation.h"
using namespace inter;

const double INF = 1e8; //infinity, not stable when >= 10^8

vector<pair<double, double> > points;

void read_points() {
	double x, y;
	while (cin >> x >> y) {
		points.push_back(make_pair(x, y));
	}
}

int main() {
	read_points(); //readin data

	Poly* li = new Poly(); //lagrange interpolation
	CubicInter* ci = new CubicInter(); //cubic interpolation
	
	//add points
	for (int i = 0; i < (int)points.size(); ++i) {
		li->push(points[i]);
		ci->push(points[i]);
	}

	//Lagrange Interpolation
	cout << "Lagrange Interpolation: " << endl;
	li->print(true);
	fprintf(stdout, "--------------------------------------------\n");

	//Cubic Interpolation
	cout << "Cubic Interpolation: " << endl;
	ci->set(CubicInter::CONDITION::FIRST, INF, 1.0 / 16.0)->print(true);
	cout << ci->get(1.0) << endl;
	
	//free memory :lol:
	delete li;
	delete ci;

	return 0;
}
