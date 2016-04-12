# 第四章 数值积分和数值微分

- **本章代码使用说明**

## 习题代码

- 源码文件`chapter4.cpp`

### 习题4.2

- 类：`Q2`

| 成员 | 类型 | 属性 | 说明 |
|:----:|:----:|:----:|:-----------------:|
| `double trape(double left, double right, int n, double (*f)(double))` | 梯形积分 | `public` | `left`为左端点，`right`为右端点，`n`为等分份数，`f`为指向被积函数的函数指针，若不指定则为常函数`f(x)=1` |
| `double simpson(double left, double right, int n, double (*f)(double) = &Q2::__fun)` | 辛普森积分 | `public` | 同上 |

- 使用举例

```

const double PI = acos(-1.0);

double my_function(double x) {
	return sin(x);
}

int main() {
	cout << fixed; //设置输出格式：强制小数输出
	cout << setprecision(8); //设置输出格式：小数位数为8
	cout << Q2::simpson(0, PI, 100, my_function)) << endl;
	return 0;
}

```
