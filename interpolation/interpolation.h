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
			CubicInter* print(bool matlab = false);
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
			NewtonInter* print(bool matlab = false);
			double get(double x);

		private:
			std::vector<std::pair<double, double> > data; /* 插值点 */
			std::vector<std::vector<double> > table; /* 均差表 */
			bool updated; /* 均差表是否计算完毕 */
	};

	/* 多项式插值(拉格朗日) */
	class Poly;
	class Poly {
		public:
			/* constructor */
			Poly();

			/* add point */
			Poly* push(std::pair<double, double> point);
			Poly* push(double x_ray, double y_ray);

			/* get size */
			size_t size() const;
			/* print & calculate */
			Poly* update();
			Poly* print(bool matlab = false);
			double get(double x);

		private:
			std::vector<std::pair<double, double> > data; /* 插值点 */
			std::vector<double> mother; /* 插值基函数分母部分 */
			bool updated;
	};
};

#endif

