/* **********************************************

  File Name: romberg.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed Apr 27 11:55:03 2016

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

const bool DEBUG = false;

/**
 * 区间[a,b]求func(x)的积分
 * 龙贝格求积基于梯形公式和外推加速，算法如下:
 * (1) 取k=1,h=b-a,求T_0^{(0)}=h/2 * [f(a) + f(b)].
 *   for 1->k
 * (2) 求T_0((b-a) / (2^h)), 按公式T_{2n}=h/4*\sum_{k=0}^{n-1}*[f(x_k)+f(x_{k+1})] + h/2*\sum_{k=0}^{n-1}*f(x_{k+1/2})算
 * (3) 求加速值，T_m^{(k)}=4^m/(4^m-1)*T_{m-1}^{(k+1)}-1/(4^m-1)*T_{m-1}^{(k)}
 * (4) 若|T_k{(0)}-T_{k-1}^{(0)}|<ε，结束，取T_k{(0)}≈I，否则令k=k+1，转2
 * 上述求解过程就是：
 * k      h     T_0{k}    T_1{k}   T_2{k} ...
 * 0     b-a    T_0{0}
 * 1   (b-a)/2  T_0{1}    T_1{0}
 * 2   (b-a)/4  T_0{2}    T_1{1}    T_2{0}
 * 3   (b-a)/8  ...
 *
 * *      *       1
 *                |
 * *      *       2   ->   3
 *                |
 * *      *       4   ->   5   ->   6
 *                |
 * *      *       7   ->   8 ...
 */
double romberg(double a, double b, double (*func)(double), double EPS = 1e-6) {
    int k = 1;
    double h = b - a, h2, h4;
    vector<vector<double> > T;
    
	T.push_back(vector<double>(1)); //first line with 1 element
	T[0][0] = 0.5 * h * (func(a) + func(b));
	
	if (DEBUG) {
		printf("%.5f\t", T[0][0]);
	}

    for(; ; k++) {
        //row k
        h2 = 0.5 * h; // (h/2)
        h4 = 0.25 * h; // (h/4)
        for (int i = k, m = 0; i >= 0; i--, m++) {
            //calculate T_{m}^{i}
            //T[k][m]=T_{m}{0}=h/4*\sum_{k=0}^{n-1}*[f(x_k)+f(x_{k+1})] + h/2*\sum_{k=0}^{n-1}*f(x_{k+1/2})
            //T[k][m]=T_{m}{>0}=4^m/(4^m-1)*T_{m-1}^{(k+1)}-1/(4^m-1)*T_{m-1}^{(k)}
            if (m) {
                T[k][m] = ((1 << (2 * m)) * T[k][m - 1] - T[k - 1][m - 1]) / ((1 << (2 * m)) - 1);
            } else {
                T.push_back(vector<double>(k + 1)); //k+1 elements in k-th row
                double sum2 = 0;
                for (int j = 1 << (k - 1); j; j--) {
                    //range[a + h2 * (j - 1), a + h2 * j]
                    sum2 += func(a + h * (j - 0.5));
                }
                T[k][m] = 0.5 * T[k - 1][m] + h2 * sum2;
            }
			if (DEBUG) {
				fprintf(stderr, "T[%d][%d] = %.6f", k, m, T[k][m]);
			}
        }
		if (DEBUG) {
			fputs("", stderr);
		}
        h = h2; //reduce delta
        if (fabs(T[k][0] - T[k - 1][0]) < EPS) {
            break;
        }
    }
    return T[k][0];
}

double fx(double x) {
    return pow(x, 1.5);
}

int main() {
    fprintf(stdout, "∫(0->1){x^1.5} = %.6f\n", romberg(0, 1, fx));
    return 0;
}
