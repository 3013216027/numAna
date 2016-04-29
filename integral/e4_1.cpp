/* **********************************************

  File Name: e4_1.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Fri, Apr 29, 2016  4:02:03 PM

*********************************************** */
#include <bits/stdc++.h>
using namespace std;

const bool DEBUG = false;

const double EPS = 1e-6;

/* ========================================梯形公式:BEGIN=========================================== */
/**
 * 梯形
 * ----------------------------------------------
 * |参数 | 参数类型           | 含义            |
 * | a/b | double             | 积分区间[a,b]   |
 * |func | double (*)(double) | 被积函数        |
 * | h   | double             | 步长，默认0.1   |
 * | EPS | double             | 精度，默认10^-6 |
 * ----------------------------------------------
 * | 返回值   | 返回值类型 | 含义     |
 * | res|res' | double     | 积分结果 |
 * ------------------------------------
 */
double trape(double a, double b, double (*func)(double), double h = 0.1, double EPS = ::EPS) {
    if (a > b) {
        swap(a, b);
    }
    if (h < 0) {
        h = -h;
    }
    if (h > b - a) {
        h = b - a;
    }
    if (DEBUG) {
        fprintf(stderr, "trap (%.5f, %.5f, %.5f)\n", a, b, h);
    }
    double res = 0.0;
    for (double left = a, right = a + h; right < b + EPS;) {
        res += 0.5 * (right - left) * (func(left) + func(right));
        if (DEBUG) {
            fprintf(stderr, "left = %.5f, right = %.5f, res => %.6f\n", left, right, res);    
        }
        left = right;
        right += h;
    }
    return res;
}
/* ========================================梯形公式:END============================================== */

/* ========================================辛普森公式:BEGIN=========================================== */
/**
 * 辛普森
 * ----------------------------------------------
 * |参数 | 参数类型           | 含义            |
 * | a/b | double             | 积分区间[a,b]   |
 * |func | double (*)(double) | 被积函数        |
 * | h   | double             | 步长，默认0.1   |
 * | EPS | double             | 精度，默认10^-6 |
 * ----------------------------------------------
 * | 返回值   | 返回值类型 | 含义     |
 * | res|res' | double     | 积分结果 |
 * ------------------------------------
 */
double simpson(double a, double b, double (*func)(double), double h = 0.1, double EPS = ::EPS) {
    if (a > b) {
        swap(a, b);
    }
    if (h < 0) {
        h = -h;
    }
    if (h > b - a) {
        h = b - a;
    }
    if (DEBUG) {
        fprintf(stderr, "simpon(%.5f, %.5f, %.5f)\n", a, b, h);
    }
    double res = 0.0;
    for (double left = a, right = a + h; right < b + EPS;) {
        res += (right - left) * (func(left) + 4.0 * func(0.5 * (left + right)) + func(right)) / 6.0;
        if (DEBUG) {
            fprintf(stderr, "left = %.6f, right = %.6f, res => %.6f\n", left, right, res);
        }
        left = right;
        right += h;
    }
    return res;
}
/* ========================================辛普森公式:END============================================== */

/* ==========================================龙贝格:BEGIN============================================== */
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
    if (a >  b) swap(a, b);
    int k = 1;
    double h = b - a;
    vector<vector<double> > T;
    
    T.push_back(vector<double>(1)); //first line with 1 element
    T[0][0] = 0.5 * h * (func(a) + func(b));
    
    if (DEBUG) {
        fprintf(stdout, "T[0][0]=%.6f\n", T[0][0]);
    }

    for(; ; k++) {
        //row k
        double h2 = 0.5 * h; // (h/2)
        double h4 = 0.25 * h; // (h/4)
        bool stop = false;
        for (int i = k, m = 0; i >= 0; i--, m++) {
            //calculate T_{m}^{i}
            //T[k][m]=T_{m}{0}=h/4*\sum_{k=0}^{n-1}*[f(x_k)+f(x_{k+1})] + h/2*\sum_{k=0}^{n-1}*f(x_{k+1/2})
            //T[k][m]=T_{m}{>0}=4^m/(4^m-1)*T_{m-1}^{(k+1)}-1/(4^m-1)*T_{m-1}^{(k)}
            if (m) {
                //case 1: m != 0
                T[k][m] = ((1 << (2 * m)) * T[k][m - 1] - T[k - 1][m - 1]) / ((1 << (2 * m)) - 1);
            } else {
                //case 2: m = 0
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
    return T[k][k];
}
/* ==========================================龙贝格:END================================================ */

/* ==========================================自适应辛普森:BEGIN=========================================== */
/**
 * 原算法为15EPS，但由于精度缺陷(如辛普森公式中的÷6导致的精度丢失)
 * 会使得期望无法达到。
 * 以下系数根据具体的机器环境以及积分函数的曲率变化程度大小调整，
 * 如本机double数据类型可保存精度为约15位有效数字，对测试函数y=x^1.5取系数<11可达到期望精度。
 */
const double TIMES = 1.0;

/**
 * 用于优化常数性能的二维向量。
 * 第一维表示当前积分之前是否已计算过，
 * 第二维为(若已计算过)积分值
 */
const std::pair<bool, double> OPT_DEFAULT = std::make_pair(false, 0);

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
double adaptive_simpson(double a, double b, double (*func)(double),
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
        return adaptive_simpson(a, mid, func, EPS, std::make_pair(true, S2_left))
            + adaptive_simpson(mid, b, func, EPS, std::make_pair(true, S2_right));
    }
}
/* ==========================================自适应辛普森:END============================================= */

/**
 * 被积函数
 * @param  x 自变量
 * @return   函数值
 * @info 函数在<=0无意义，此时直接返回fx(x->+0)=fx(EPS)
 */
inline double fx(double x) {
    if (x < EPS) {
        return fx(EPS);
    }
    return sqrt(x) * log(x);
}

/**
 * 读入步长数据
 */
std::vector<double> step;
bool read_step(const char* filename = "e4_1.in") {
    FILE* fp = fopen(filename, "r");
    if (fp != NULL) {
        step.clear();
        double tmp;
        while (fscanf(fp, "%lf", &tmp) != EOF) {
            step.push_back(tmp);
        }
        fclose(fp);
        return true;
    } else {
        fprintf(stderr, "File (%s) open failed!", filename);
        return false;
    }
}

void gao() {
    /* Pro.1 */
    //fprintf(stdout, "(1)\n");
    if (!read_step()) {
        exit(1);
    }
    fprintf(stdout, "---------------------------------------------------------------\n");
    fprintf(stdout, "%-12s%-20s%-20s%-20s%-30s\n", "step", "trape-integral",
        "simpson-integral", "romberg-integral", "adaptive_simpon-integral");
    double res_romberg = romberg(0, 1, fx);
    double res_adaptive_simpson = adaptive_simpson(0, 1, fx, 1e-6);
    for (auto it: step) {
        
        fprintf(stdout, "%-12.6f%-20.6f%-20.6f%-20.6f%-30.6f\n", it,
            trape(0, 1, fx, it),
            simpson(0, 1, fx, it),
            res_romberg,
            res_adaptive_simpson
        );
    }
    fprintf(stdout, "---------------------------------------------------------------\n");
}

int main() {
    gao();
    fflush(stdout);
    fflush(stderr);
    
    system("pause");
    return 0;
}
