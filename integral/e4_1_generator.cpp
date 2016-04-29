/* **********************************************

  File Name: e4_1_generator.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Fri, Apr 29, 2016  5:27:21 PM

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

int main() {
    double len = 1.0;
    const double EPS = 1e-6;
    fprintf(stdout, "%.6f\n", len);
    while (len > EPS) {
        fprintf(stdout, "%.6f\n", len *= 0.5);
    }
    return 0;
}
