/* **********************************************

  File Name: interpolation.cpp

  Author: zhengdongjian@tju.edu.cn

  Created Time: Tue Mar 29 16:42:42 2016

*********************************************** */

#include <cstdio>
#include <cassert>
#include <algorithm>

#include "interpolation.h"

/**
 * 三次插值
 */
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

/* constructor */
inter::CubicInter::CubicInter() {
	this->condition_type = CONDITION::NONE;
	this->data.clear();
}

inter::CubicInter::CubicInter(int size):inter::CubicInter::CubicInter() {
	//fprintf(stderr, "init with size %d\n", size);
	//this->data.resize(size);
}


/* get size of data */
inline size_t inter::CubicInter::size() const {
	return this->data.size();
}


/* add point */
inline inter::CubicInter* inter::CubicInter::push(double x_ray, double y_ray) {
	this->push(std::make_pair(x_ray, y_ray));
	return this;
}

inline inter::CubicInter* inter::CubicInter::push(std::pair<double, double> point) {
	this->data.push_back(point);
	return this;
}


/* remove point */
inline inter::CubicInter* inter::CubicInter::pop() {
	this->data.pop_back();
	return this;
}

inline inter::CubicInter* inter::CubicInter::erase(size_t index) {
	if (index == this->size() - 1) {
		return this->pop();
	}
	this->data.erase(this->data.begin() + index);
	return this;
}

inline inter::CubicInter* inter::CubicInter::erase(size_t index, size_t count) {
	if (count == 1) {
		return this->erase(index);
	}
	this->data.erase(this->data.begin() + index, this->data.begin() + index + count);
	return this;
}


/* set init condition */
inter::CubicInter* inter::CubicInter::set(inter::CubicInter::CONDITION condition, double val_left, double val_right) {
	this->condition_type = condition;
	this->val_left = val_left;
	this->val_right = val_right;
	return prepare();
}

inter::CubicInter* inter::CubicInter::prepare() {
	H = std::vector<double>(this->size() - 1); /* H[j] = X[j + 1] - X[j], X[j] = this->data[j].first */
	std::vector<double> U(this->size() - 1); /* U[j] = H[j - 1] / (H[j - 1] + H[j]), use U[j] as U[j - 1] */
	std::vector<double> V(this->size() - 1); /* V[j] = H[j] / (H[j - 1] + H[j]), Lambda */
	std::vector<double> D(this->size()); /* D[j] = 6 * f[x[j - 1], x[j], x[j + 1]] */
	int sz = this->size() - 1;

	std::sort(data.begin(), data.end());

	/* cal H[] */
	for (int i = 0; i < sz; ++i) {
		H[i] = data[i + 1].first - data[i].first;
	}

	for (int j = 1; j < sz; ++j) {
		U[j - 1] = H[j - 1] / (H[j - 1] + H[j]);
		V[j] = H[j] / (H[j - 1] + H[j]);
	}

	for (int k = 1; k < sz; ++k) {
		double tp1 = (data[k + 1].second - data[k].second) / (data[k + 1].first - data[k].first);
		double tp2 = (data[k].second - data[k - 1].second) / (data[k].first - data[k - 1].first);
		D[k] = 6.0 * (tp1 - tp2) / (data[k + 1].first - data[k - 1].first);
	}

	std::vector<double> two(sz + 1, 2);
	if (this->condition_type == CONDITION::FIRST) {
		V[0] = U[sz - 1] = 1;
		D[0] = 6.0 / H[0] * ((data[1].second - data[0].second) / (data[1].first - data[0].first) - val_left);
		D[sz] = 6.0 / H[sz - 1] * (val_right - (data[sz].second - data[sz - 1].second) / (data[sz].first - data[sz - 1].first));
		M = inter::CubicInter::pursuit(U, two, V, D);
	} else if (this->condition_type == CONDITION::SECOND) {
		V[0] = U[sz - 1] = 0;
		D[0] = 2.0 * val_left;
		D[sz] = 2.0 * val_right;
		M = inter::CubicInter::pursuit(U, two, V, D);
	} else if (this->condition_type == CONDITION::THRID) {
		M = std::vector<double>(sz + 1, -1);
	} else {
		assert(false);
	}

	/*
	fprintf(stderr, "U = ");
	CubicInter::print(U);
	fprintf(stderr, "V = ");
	CubicInter::print(V);
	fprintf(stderr, "D = ");
	CubicInter::print(D);
	*/
	return this;
}

/* print */
inter::CubicInter* inter::CubicInter::print() {
	fprintf(stdout, "S(x) = \n");
	int sz = this->size() - 1;
	for (int j = 0; j < sz; ++j) {
		fprintf(
				stdout, "  %.5f <= x <= %.5f:  %.5f * (%.5f - x)^3 + %.5f * (x - %.5f)^3 + %.5f * (%.5f - x) + %.5f * (x - %.5f)\n",
				data[j].first, data[j + 1].first,
				M[j] / 6.0 / H[j], data[j + 1].first, M[j + 1] / 6.0 / H[j], data[j].first,
				data[j].second / H[j] - M[j] * H[j] / 6.0, data[j + 1].first,
				data[j + 1].second / H[j] - M[j + 1] * H[j] / 6.0, data[j].first
		);
	}
	return this;
}

inline double pow3(double x) {
	return x * x * x;
}

double inter::CubicInter::get(double x) {
	double sum = 0.0;
	int sz = this->size();
	for (int j = 0; j < sz; ++j) {
		sum += M[j] / 6.0 / H[j] * pow3(data[j + 1].first - x);
		sum += M[j + 1] / 6.0 / H[j] * pow3(x - data[j].first);
		sum += (data[j].second / H[j] - M[j] * H[j] / 6.0) * (data[j + 1].first - x);
		sum += (data[j + 1].second / H[j] - M[j + 1] * H[j] / 6.0) * (x - data[j].first);
	}
	return sum;
}

/**
 * 牛顿插值
 *
 *
 *
 */

inter::NewtonInter::NewtonInter() {
	this->table.clear();
	this->data.clear();
	this->updated = false;
}

/* add point */
inline inter::NewtonInter* inter::NewtonInter::push(double x_ray, double y_ray) {
	this->push(std::make_pair(x_ray, y_ray));
	return this;
}

inline inter::NewtonInter* inter::NewtonInter::push(std::pair<double, double> point) {
	this->data.push_back(point);
	return this;
}


/* remove point */
inline inter::NewtonInter* inter::NewtonInter::pop() {
	this->data.pop_back();
	return this;
}

inline inter::NewtonInter* inter::NewtonInter::erase(size_t index) {
	if (index == this->size() - 1) {
		return this->pop();
	}
	this->data.erase(this->data.begin() + index);
	return this;
}

inline inter::NewtonInter* inter::NewtonInter::erase(size_t index, size_t count) {
	if (count == 1) {
		return this->erase(index);
	}
	this->data.erase(this->data.begin() + index, this->data.begin() + index + count);
	return this;
}

/* get size */
inline size_t inter::NewtonInter::size() const {
	return data.size();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * update
 * x0 f0
 * x1 f1 f[0,1]
 * x2 f2 f[1,2] f[0,1,2]
 * x3 f3 f[2,3] f[1,2,3] f[0,1,2,3]
 * x4 f4 f[3,4] f[2,3,4] f[1,2,3,4] f[0,1,2,3,4]
 * x5 f5 f[4,5] f[3,4,5] f[2,3,4,5] f[1,2,3,4,5] f[0,1,2,3,4,5]
 * ...
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
inter::NewtonInter* inter::NewtonInter::update() {
	if (!this->updated) {
		std::sort(this->data.begin(), this->data.end());
		// resize table
		table.clear();
		int lines = size();
		for (int i = 0; i < lines; ++i) {
			table.push_back(std::vector<double>(i + 1));
		}
		// fill table
		for (int i = 0; i < lines; ++i) {
			table[i][0] = data[i].second;
		}
		for (int i = 1; i < lines; ++i) {
			for (int j = i; j < lines; ++j) {
				//table[j][i]
				table[j][i] = (table[j][i - 1] - table[j - 1][i - 1]) / (data[j].first - data[i - 1].first);
			}
		}
		this->updated = true;
	}
	return this;
}

inter::NewtonInter* inter::NewtonInter::print() {
	fprintf(stdout, "S(x) = \n");
	int lines = size();
	for (int i = 0; i < lines; ++i) {
		fprintf(stdout, "    %.5f", table[i][i]);
		for (int j = 0; j < i; ++j) {
			fprintf(stdout, " * (x - %.5f)", data[j + 1].first);
		}
		fprintf(stdout, "%s", i == lines - 1 ? "\n\n" : "\n  + ");
	}
	return this;
}

double inter::NewtonInter::get(double x) {
	int lines = size();
	double result = 0.0;
	for (int i = 0; i < lines; ++i) {
		double tp = table[i][i];
		for (int j = 0; j < i; ++j) {
			tp *= (x - data[j + 1].first);
		}
		result += tp;
	}
	return result;
}
