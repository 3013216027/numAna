/* **********************************************

  File Name: interpolation.h

  Author: zhengdongjian@tju.edu.cn

  Created Time: Tue Mar 29 16:41:58 2016

*********************************************** */
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>
#include <utility>
#include <cassert>

namespace inter {
	/* !! data class: double !! */

	//using std::vector;
	//typedef dataType double;
	/* 三次样条插值 */
	class CubicInter;
	class CubicInter {
		public:
			/* init condition types */
			enum CONDITION {
				FIRST, /* 一次导数 */
				SECOND, /* 二次导数 */ 
				THRID, /* 周期函数 */
				NONE /* NULL */
			};

			/* 追赶法求对角占优三对角线方程组 */
			static std::vector<double> pursuit(
					const std::vector<double>& A,
					const std::vector<double>& B,
					const std::vector<double>& C,
					const std::vector<double>& F
					);

			/* print array */
			static void print(const std::vector<double>& tp);

			/* constructor */
			CubicInter();
			CubicInter(int size);

			/* get size of data */
			size_t size() const;

			/* add point */
			CubicInter* push(double x_ray, double y_ray);
			CubicInter* push(std::pair<double, double> point);

			/* remove point */
			CubicInter* erase(size_t index);
			CubicInter* erase(size_t index, size_t count);
			CubicInter* pop();

			/* set init condition */
			CubicInter* set(CubicInter::CONDITION condition, double val_left, double val_right);
			CubicInter* prepare();

			/* print&caculate */
			CubicInter* print();
			double get(double x);

		private:
			std::vector<std::pair<double, double> > data;
			std::vector<double> H, M;
			CubicInter::CONDITION condition_type;
			double val_left;
			double val_right;
	};

	/* 牛顿插值 */
	class NewtonInter;
	class NewtonInter {
		public:

			/* constructor */
			NewtonInter();

			/* add point */
			NewtonInter* push(std::pair<double, double> point);
			NewtonInter* push(double x_ray, double y_ray);

			/* remove point */
			NewtonInter* erase(size_t index);
			NewtonInter* erase(size_t index, size_t count);
			NewtonInter* pop();

			/* get size */
			size_t size() const;
			/* print&calculate */
			NewtonInter* update();
			NewtonInter* print();
			double get(double x);

		private:
			std::vector<std::pair<double, double> > data; /* 插值点 */
			std::vector<std::vector<double> > table; /* 均差表 */
			bool updated; /* 均差表是否计算完毕 */
	};
};

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 追赶法求对角占优三对角线方程组
 * ___                                ___  __       __     __       __
 * | b1 c1                              |  |   x1    |     |   f1    |
 * | a2 b2 c2                           |  |   x2    |     |   f2    |
 * |    a3 b3 c3                        |  |   x3    |     |   f3    |
 * |       .  .  .                      |  |   .     |     |   .     |
 * |         .  .  .                    |  |   .     |  =  |   .     |
 * |           .  .  .                  |  |   .     |     |   .     |
 * |             a_{n-1} b_{n-1} c_{n-1}|  | x_{n-1} |     | f_{n-1} |
 * |                     a_n     b_n    |  |  x_n    |     |   f_n   |
 * ---                                ---  --       --     --       --
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
std::vector<double>
inter::CubicInter::pursuit(const std::vector<double>& A, const std::vector<double>& B,
	const std::vector<double>& C, const std::vector<double>& F) {
	// array A has offset of 1 !!
	assert(A.size() == B.size() - 1);
	assert(A.size() == C.size());
	assert(A.size() == F.size() - 1);

	std::vector<double> beta(A.size());
	std::vector<double> Y(B.size());

	beta[0] = C[0] / B[0];
	for (int i = 1; i < (int)beta.size(); ++i) {
		beta[i] = C[i] / (B[i] - A[i - 1] * beta[i - 1]);
	}

	Y[0] = F[0] / B[1];
	for (int j = 1; j < (int)Y.size(); ++j) {
		Y[j] = (F[j] - A[j - 1] * Y[j - 1]) / (B[j] - A[j - 1] * beta[j - 1]);
	}

	std::vector<double> res(B.size());
	res[res.size() - 1] = Y[res.size() - 1];
	for (int k = res.size() - 2; k >= 0; --k) {
		res[k] = Y[k] - beta[k] * res[k + 1];
	}

	/*
	for (int i = 0; i < (int)res.size(); ++i) {
		printf("%.6f\t", res[i]);
	}
	puts("");
	*/

	return res;
}

/* print array */
void inter::CubicInter::print(const std::vector<double>& tp) {
	fprintf(stderr, "[ ");
	int sz = tp.size();
	for (int i = 0; i < sz; ++i) {
		fprintf(stderr, "%.5f%s", tp[i], i == sz - 1 ? " ]" : ", ");
	}
}


#endif

