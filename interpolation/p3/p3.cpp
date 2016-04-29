/* **********************************************

  File Name: p3.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed 20 Apr 2016 09:39:42 PM CST

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

#include "../interpolation.h"
using namespace inter;

const double INF = 100; //infinity, not stable when >= 10^8

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
	// for (int i = 0; i < 65; ++i) {
	// 	cout << i << " -> " << li->get(i) << endl;
	// }
	fprintf(stdout, "--------------------------------------------\n");

	//Cubic Interpolation
	cout << "Cubic Interpolation: " << endl;
	ci->set(CubicInter::CONDITION::FIRST, INF, 1.0 / 16.0)->print(true);
	// for (int i = 0; i < 65; ++i) {
	// 	 cout << i << " => " << ci->get(i) << endl;
	// }
	
	//free memory :lol:
	delete li;
	delete ci;

	system("pause");
	return 0;
}
