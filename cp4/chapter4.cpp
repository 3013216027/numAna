/* **********************************************

	File Name: chapter4.cpp

	Author: zhengdongjian@tju.edu.cn

	Created Time: Tue Apr 12 20:16:06 2016

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

class Q2 {
	public:
	static double trape(double left, double right, int n, double (*f)(double) = &Q2::__fun) {
		double h = (right - left) / n;
		double sum = 0.0;
		double le = left - h, ri;
		for (int i = 0; i < n; ++i) {
		le += h;
		ri = le + h;
		sum += 0.5 * h * (f(le) + f(ri));
		}
		return sum;
	}

	static double simpson(double left, double right, int n, double (*f)(double) = &Q2::__fun) {
		double h = (right - left) / n;
		double sum = 0.0;
		double le = left - h, ri;
		for (int i = 0; i < n; ++i) {
		le += h;
		ri = le + h;
		sum += h * (f(le) + 4.0 * f((le + ri) * 0.5) + f(ri)) / 6.0;
		}
		return sum;
	}

	static double __fun(double x) {
		return 1;
	}
};

const double PI = acos(-1.0);

double my_function(double x) {
	return sqrt(4.0 - sin(x) * sin(x));
}

int main() {
	cout << fixed << setprecision(8);
	cout << Q2::trape(0, PI / 6.0, 6, my_function) << endl;
	cout << Q2::simpson(0, PI / 6.0, 6, my_function) << endl;
	return 0;
}
