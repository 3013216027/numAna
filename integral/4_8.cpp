/* **********************************************

  File Name: 4_8.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Wed Apr 27 12:59:11 2016

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

const bool DEBUG = true;

/**
 * ----------------------------------------------
 * |参数 | 参数类型           | 含义            |
 * | a/b | double             | 积分区间[a,b]   |
 * |func | double (*)(double) | 被积函数        |
 * | EPS | double             | 精度，默认10^-6 |
 * ----------------------------------------------
 * | 返回值  | 返回值类型 | 含义     |
 * | T[k][k] | double     | 积分结果 |
 * -----------------------------------
 */
double romberg(double a, double b, double (*func)(double), double EPS = 1e-6) {
    int k = 1;
    double h = b - a, h2, h4;
    vector<vector<double> > T;
    
    T.push_back(vector<double>(1)); //first line with 1 element
    T[0][0] = 0.5 * h * (func(a) + func(b));
    
    if (DEBUG) {
        fprintf(stdout, "T[0][0]=%.6f\n", T[0][0]);
    }

    for(; ; k++) {
        //row k
        h2 = 0.5 * h; // (h/2)
        h4 = 0.25 * h; // (h/4)
        bool stop = false;
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
                fprintf(stdout, "T[%d][%d]=%.6f ", k, m, T[k][m]);
            }
            if (i != 0 && fabs(T[k][m] - T[k - 1][m]) < EPS) {
                stop = true;
            }
        }
        if (DEBUG) {
            fprintf(stdout, "\n");
        }
        h = h2; //reduce delta
        if (k > 1 && stop) {
            break;
        }
    }
    if (DEBUG) {
        fprintf(stdout, "finally got T[%d][%d] = %.6f\n", k, k, T[k][k]);
    }
    return T[k][k];
}

double f1(double x) {
    return exp(-x);
}

double f2(double x) {
    return x * sin(x);
}

double f3(double x) {
    return x * sqrt(1 + x * x);
}

int main() {
    //cout << sin(2 * PI) << endl;
    double eps = 1e-5;
    fprintf(stdout, "第四章第8题：\n");
    fprintf(stdout, "(1) 2/sqrt(π)*∫(0->1){e^-x}dx = %.6f\n", 2.0 / sqrt(PI) * romberg(0, 1, f1, eps) + 1e-7);
    fprintf(stdout, "--------------------------------------------------------------------------------------\n");
    fprintf(stdout, "(2) ∫(0->2π){x*sin(x)}dx = %.6f\n", romberg(0, 2 * PI, f2, eps) + 1e-7);
    fprintf(stdout, "--------------------------------------------------------------------------------------\n");
    fprintf(stdout, "(3) ∫(0->3){x*sqrt(1+x^2)}dx = %.6f\n", romberg(0, 3, f3, eps) + 1e-7);
    fprintf(stdout, "--------------------------------------------------------------------------------------\n");
    return 0;
}
