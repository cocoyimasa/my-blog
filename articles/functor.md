### 实现任意个数参数的函数指针

V8中回调函数的函数指针原型为Handle<Value> Callback(const Arguments& args);

将参数抽象成类，将返回值抽象为模板句柄，从而实现回调函数和参数类型、参数个数、返回值不相关，这也是一种解耦合。

Argument只需提供参数读写成员函数即可，这与C语言中的...的va_start、va_arg函数组有异曲同工之妙。

而一般函数指针都指定返回值和参数类型，这种无法通用。


另外的方式（C++11以上支持）：变长模板参数。

获取变长模板参数：递归获取。方式：建立无模板参数的函数，其他函数递归获取。

例：
```Cpp
template<>
struct count<>{
    static const int value = 0;
}
template<typename T, typename ...Args>
struct count<T, Args...>{
    static const int value = 1 + count<Args...>::value;
}
```
