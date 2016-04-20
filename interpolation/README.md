
- 文件结构
 - `interpolation.cpp` `interpolation.h`: 核心库，包含拉格朗日多项式插值、牛顿插值和三次样条插值
 - `test/`: 各插值法样例测试，直接使用`make`编译，然后`make run`即可运行测试程序
 - `e1_20/`: 习题1.20(第五版)
 - `p1/`: 计算实习题1
 - `p3/`: 计算实习题3

# Interpolation API

- `namespace`: `inter`

## CubicInter

### `public`

- `CONDITION`
 - `FIRST`: first type
 - `SECOND`: second type
 - `THRID`: thrid type
 - `NONE`: null(not set yet)

- add a point:

```
using inter::CubicInter;

CubicInter* p = new CubicInter;
p->push(1.0, 3.0);
//or
p->push(make_pair(3.0, 5.0));
//and
p->push(4.0, 4.0)->push(5.0, 5.0);
```

- remove a point:

```
using inter::CubicInter;

CubicInter* p = new CubicInter;
p->push(4.0, 4.0)->push(5.0, 5.0)->push(1.0, 3.0)->push(0, 10.0);

//remove the last point
p->pop();
//or remove the second point
p->erase(1);
//or remove the first two points
p->erase(0, 2);
```

- get result:

```
using inter::CubicInter;

CubicInter* p = new CubicInter;
p->push(4.0, 4.0)->push(5.0, 5.0)->push(1.0, 3.0)->push(0, 10.0);

//set condition with first type
p->set(CubicInter::FIRST, 1.0, 2.0);

//print result
p->print();
```

## NewtonInter

- demo:

```
using namespace inter;

NewtonInter* p = new NewtonInter;

p->push(4.0, 4.0)->push(5.0, 5.0)->push(1.0, 3.0)->push(0, 10.0);

p->print();
```

## Poly

- demo:

```
using namespace inter;

Poly* p = new Poly();

p->push(4.0, 4.0)->push(5.0, 2)->push(-1, 3)->print();

std::cout << (p->get(3.0)) << std::endl;
```
