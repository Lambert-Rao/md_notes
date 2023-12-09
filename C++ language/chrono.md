---
title: "c++ chrono"
type: page
---
 

https://zhuanlan.zhihu.com/p/623543334

### 时钟

C++11 的 chrono 库主要包含了三种类型的时钟：

| 名称                  | 说明                           |
| --------------------- | ------------------------------ |
| system_clock          | 来自系统范畴实时时钟的挂钟时间 |
| steady_clock          | 不因系统变化的单调时钟         |
| high_resolution_clock | 可用的最短周期的时钟           |

成员

| 名称       | 说明                                                         |
| ---------- | ------------------------------------------------------------ |
| now()      | 静态成员函数，返回当前时间，类型为clock::time_point          |
| time_point | 成员类型，当前时钟的时间点类型。                             |
| duration   | 成员类型，时钟的时长类型。                                   |
| rep        | 成员类型，时钟的tick类型，等同于clock::duration::rep         |
| period     | 成员类型，时钟的单位，等同于clock::duration::period          |
| is_steady  | 静态成员类型：是否是稳定时钟，对于steady_clock来说该值一定是true |

静态成员函数 new() 来获取当前时间

system_clock 提供了两个静态成员函数来与 std::time_t 进行互相转换：

| 名称        | 说明                              |
| ----------- | --------------------------------- |
| to_time_t   | 转换系统时钟时间点为 std::time_t  |
| from_time_t | 转换 std::time_t 到系统时钟时间点 |

### 时长

类模板 std::chrono::duration 表示时间间隔。

| 函数          | 说明                                         |
| ------------- | -------------------------------------------- |
| duration_cast | 进行时长的转换                               |
| floor (C++17) | 以向下取整的方式，将一个时长转换为另一个时长 |
| ceil (C++17)  | 以向上取整的方式，将一个时长转换为另一个时长 |
| round (C++17) | 转换时长到另一个时长，就近取整，偶数优先     |
| abs (C++17)   | 获取时长的绝对值                             |

 point.time_since_epoch

### 时间点

clock::now()

