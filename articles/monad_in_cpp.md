## C++模拟Haskell的Monad

模拟Monad主要是为了写语法分析器简便。

之前试着用C#模拟，好麻烦。。改用C++之后一路通畅。

只要支持模板、支持lambda表达式或函数指针或委托，且能重载运算符的强类型语言其实都可以。

```
template<typename T>
class Monad {
public:
    T* val;
    Monad() {

    }
    Monad(T* a) {
        this->val = a;
    }
};

template<typename T,typename K>
Monad<K>* operator>>(Monad<T>* a, function<Monad<K>*(T*)> f) { //>>=,chain
    return f(a->val);
}
template<typename T>
Monad<T>* id(T* a) { //pack,return
    return new Monad<T>(a);
}
```

然后Parser就可以写成这样:

```
class Parser {
public:
    int id;
    Parser() {

    }
    Parser(int id) {
        this->id = id;
    }
    virtual void Parse() {
        // do something
    }
};
Parser* p = new Parser(1);
Monad<Parser>* pm = id(p);
//StatementParser, IfParser, ForParser, ExpressionParser,EndParser 是 Parser的子类
function<Monad<Parser>*(Parser*)> f = [](Parser* a) {
    a->Parse();
    return new Monad<Parser>(new StatementParser(a->id + 1));
};
function<Monad<Parser>*(Parser*)> g = [](Parser* a) {
    a->Parse();
    return new Monad<Parser>(new IfParser(a->id + 1));
};
function<Monad<Parser>*(Parser*)> h = [](Parser* a) {
    a->Parse();
    return new Monad<Parser>(new ForParser(a->id + 1));
};
function<Monad<Parser>*(Parser*)> m = [](Parser* a) {
    a->Parse();
    return new Monad<Parser>(new ExpressionParser(a->id + 1));
};
function<Monad<Parser>*(Parser*)> end = [](Parser* a) {
    a->Parse();
    return new Monad<Parser>(new EndParser(a->id + 1));
};
Monad<Parser>* parserS = pm >> f >> g >> h >> m >> end; //做的基础设施就是为了这样串起来
```

只需要把各环节的小的Parser函数f定义好，串联起来形成各种文法表达式，再汇集起来，就是完整的组合子风格语法分析器（Parser Combinator）。

我仅仅写的是一个示例，基本啥事没做。

后面的事。。。慢慢做吧。精力和编程热情都大不如三年前了，根本找不到当年深夜三点调代码的状态了。

也许就没有后续了。

以上。
