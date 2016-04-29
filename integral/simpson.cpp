/* **********************************************

  File Name: simpson.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Thu, Apr 28, 2016 11:05:53 PM

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

const bool DEBUG = false;

/**
 * 原算法为15EPS，但由于精度缺陷(如辛普森公式中的÷6导致的精度丢失)
 * 会使得期望无法达到。
 * 以下系数根据具体的机器环境以及积分函数的曲率变化程度大小调整，
 * 如本机double数据类型可保存精度为约15位有效数字，对测试函数y=x^1.5取系数<11可达到期望精度。
 */
const double TIMES = 10.0;

/**
 * 用于优化常数性能的二维向量。
 * 第一维表示当前积分之前是否已计算过，
 * 第二维为(若已计算过)积分值
 */
const std::pair<bool, double> OPT_DEFAULT = std::make_pair(false, 0);

/**
 * 自适应辛普森
 * simpson(a,b) = (b-a)/6 * [f(a) + 4f((a+b)/2) + f(b)]
 * 设当前迭代区间为[left,right]，S1=simpson(left, right)
 * 令mid=(left + right) / 2, S2=simpson(left, mid) + simpson(mid, right)
 * 则若|S-S2| < 15EPS，则该区间可取S2为积分值；
 * 否则对区间[left,mid]和[mid,right]继续迭代
 */

/**
 * ---------------------------------------------------
 * |参数 | 参数类型           | 含义                 |
 * | a/b | double             | 积分区间[a,b]        |
 * |func | double (*)(double) | 被积函数             |
 * | EPS | double             | 精度，默认10^-6      |
 * | opt | pair<>             | 常数优化辅助，勿传入 |
 * ---------------------------------------------------
 * | 返回值   | 返回值类型 | 含义     |
 * | res|res' | double     | 积分结果 |
 * ------------------------------------
 */

double simpson(double a, double b, double (*func)(double),
    double EPS = 1e-6, std::pair<bool, double> opt = OPT_DEFAULT) {
    if (a >  b) swap(a, b);
    double mid = 0.5 * (a + b);
    if (DEBUG) {
        fprintf(stdout, "--------------------------------------------");
        fprintf(stdout, "cut range[%.6f, %.6f] with %.6f\n", a, b, mid);
    }
    double S1 = opt.first ? opt.second : (b - a) / 6.0 * (func(a) + 4.0 * func(mid) + func(b));
    double S2_left = (mid - a) / 6.0 * (func(a) + 4.0 * func(0.5 * (a + mid)) + func(mid));
    double S2_right = (b - mid) / 6.0 * (func(mid) + 4.0 * func(0.5 * (mid + b)) + func(b));
    if (fabs(S1 - S2_left - S2_right) < TIMES * EPS) {
        if (DEBUG) {
            fprintf(stdout, "|%.6f - %.6f| < %.6f\n", S1, S2_left + S2_right, TIMES * EPS);
        }
        return S2_left + S2_right;
    } else {
        if (DEBUG) {
            fprintf(stdout, "|%.6f - %.6f| >(=) %.6f\n", S1, S2_left + S2_right, TIMES * EPS);
        }
        return simpson(a, mid, func, EPS, std::make_pair(true, S2_left))
            + simpson(mid, b, func, EPS, std::make_pair(true, S2_right));
    }
}

double fx(double x) {
    return pow(x, 1.5);
}

int main() {
    fprintf(stdout, "∫(0->1){x^1.5} = %.6f\n", simpson(0, 1, fx));
    return 0;
}
