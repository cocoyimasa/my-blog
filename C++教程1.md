### C语言基础

#include

标准库，主函数，主函数的参数(argc,argv)和返回值

符号（数学符号，逻辑符号），

变量，基础类型（char,short,int,long,long long,float,double,long double）,数组，指针，数组指针，指针数组，char*

逻辑表达式，

条件判断（if,switch），

循环(for,while),

函数

结构体

IO -- FILE*, fopen,fread,fscanf,fprintf,fseek

----------
### C++基础

namesapce

类型（bool，wchar_t）,宽字元,IO: stdio(cin,cout,endl), iostream,istream,ostream

指针和函数指针, void* ，指针和引用

字符串，字符串和char* ，c_str()

结构体和类，new和delete运算符，访问权限（public，private，protected），成员函数，成员变量，友元。

函数重载，运算符重载。

继承，继承修饰符（public，private，protected）。

虚函数，虚基类，虚析构函数，纯虚函数，虚拟继承。

多态。运算符 static_cast<>,reinterpret_cast<>, const_cast<>；dynamic_cast<>、typeid(RTTI开启)。

const,static,const修饰变量（const int \*, int const \*, const static int \*），const修饰函数（ void func()const; ）,static修饰变量和函数。

模板(template<typename ...>)，模板元编程，迭代器，容器

#if...#endif, #ifdef...#else...#endif,#ifundef, 不定参数函数，...运算符、va_start,va_end,va_arg函数组

宏(macro)，#define

### C++11

lambda expression

decltype

std::move

智能指针（shared_ptr,weak_ptr,unique_ptr）

auto，自动类型推断

enum class

变长模板参数 template<typename T,typename ...Args>: 计算变长部分参数个数： sizeof...(Args)

-------------------------------------------

### 其他概念：

面向组合子编程

Monad

Monad就是具备将嵌套调用打平，成为链式组合调用的结构。因为实现了flatMap运算符。
