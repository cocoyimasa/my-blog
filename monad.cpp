#include <iostream>
#include <functional>
#include <cstdlib>
using namespace std;

//#define TS(T) L"Handle<"#T">"

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
class Token{
public:
	Token(){}
};
class Node{
public:
	Node(){
	}
};
class Statement: public Node{
public:
	Statement(){
	}
};
class Expression: public Node{
public:
	Expression(){
	}
};
bool match(Token x,Token y){
	return x==y;
}
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

class StatementParser: public Parser {
public:
	StatementParser() {

	}
	StatementParser(int id) {
		this->id = id;
	}
	void Parse() {
		// do something
	}
};

class ExpressionParser : public Parser {
public:
	ExpressionParser() {

	}
	ExpressionParser(int id) {
		this->id = id;
	}
	void Parse() {
		// do something
	}
};
class IfParser : public Parser {
public:
	Expression cond;
	Statement body;
	IfParser() {

	}
	IfParser(int id) {
		this->id = id;
	}
	void Parse() {
		match
	}
};

class ForParser : public Parser {
public:
	ForParser() {

	}
	ForParser(int id) {
		this->id = id;
	}
	void Parse() {
		// do something
	}
};
class EndParser : public Parser {
public:
	EndParser() {

	}
	EndParser(int id) {
		this->id = id;
	}
	void Parse() {
		// do nothing
	}
};

int main() {
	int val = 10;
	Parser* p = new Parser(1);
	Monad<Parser>* pm = id(p);
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
	Monad<Parser>* parserS = pm >> f >> g >> h >> m >> end; //做的基础设施就是为了这样串起来..
	//基础设施
	function<Monad<Parser>*(Parser*)> operator| = [](function<Monad<Parser>* a) {
		//...
		return function<Monad<Parser>*(Parser*)>(???);
	};
	function<Monad<Parser>*(Parser*)> Optional = [](function<Monad<Parser>* a) {
		//...
		return function<Monad<Parser>*(Parser*)>(???);
	};
	function<Monad<Parser>*(Parser*)> KleeneStar = [](function<Monad<Parser>* a) {
		//...
		return function<Monad<Parser>*(Parser*)>(???);
	};
	//统一风格的函数，名字使用XXX，考虑生成用宏这一系列函数
	function<Monad<Parser>*(Parser*)> XXX_F = [](Parser* a) {
		a->Parse(TokenList,startIterator);//先parser上一步的Token，然后生成本步的parser.
		return new Monad<Parser>(new XXXParser(TokenList,startIterator));
	};
	//基础表达式
	Monad<Parser>* Nop = id(NULL);
	Monad<Parser>* Identify = id(TokenType.Identify);
	Monad<Parser>* CharNumberVal = id(TokenType.Char);
	Monad<Parser>* ShortNumberVal = id(TokenType.Short);
	Monad<Parser>* IntNumberVal = id(TokenType.Int);
	Monad<Parser>* LongNumberVal = id(TokenType.Long);
	Monad<Parser>* FloatNumberVal = id(TokenType.Float);
	Monad<Parser>* DoubleNumberVal = id(TokenType.Double);
	Monad<Parser>* StringVal = id(TokenType.String);
	Monad<Parser>* BoolVal = id(TokenType.Bool);
	
	Monad<Parser>* BaseVal = Identify | CharNumberVal | ShortNumberVal | IntNumberVal | LongNumberVal |
		FloatNumber | DoubleNumberVal | StringVal | BoolVal;
	//类型
	Monad<Parser>* Type = Keyword('char') | Keyword('short') | Keyword('int') | Keyword('long')
		Keyword('float') | Keyword('double') | Keyword('string') | Keyword('bool');
	//数组
	Monad<Parser>* Array = OP('{')>> Base_F >> KleeneStar(OP(',') >> BaseVal_F) >> OP('}') | OP('{')>> Number_F(0) >>OP('}')
	//算术表达式
	Monad<Parser>* F = OP('(') >> E_F >> OP(')') | Number;
	Monad<Parser>* Tp = (OP('*')|OP('/')) >> F_F | Nop_F;
	Monad<Parser>* T = F_F >> Tp_F;
	Monad<Parser>* Ep = (OP('+')|OP('-')) >> T_F | Nop_F;
	Monad<Parser>* E = T_F >> Ep_F;
	//逻辑表达式，可参照算术表达式文法形式
	Monad<Parser>* Binary_F = ...;
	//
	Monad<Parser> Unary = ( OP(!) | OP('+') | OP('-') | OP('::') )Expression;
	
	Monad<Parser>* Expression = Identify >> Identify_F| BaseVal >> BaseVal_F | Unary_F | Binary_F | Ternary_F;
	Monad<Parser>* Arg_List = Type >> Type_F >> Identify_F >> KleeneStar(OP(',') >> Type_F >> Identify_F) | Nop;//形参列表
	Monad<Parser>* bindSt = Type >> Type_F >> Identify_F >> OP('=') >> Expression_F;
	Monad<Parser>* Statement = bindSt | IF | ELSE | FOR | FUNCTION | CLASS;
	Monad<Parser>* Body = Statement >> Statement_F >> KleeneStar(Statement_F) | Nop;
	
	Monad<Parser>* IF = Keyword_F('IF') >> OP('(') >> Expression_F >> OP(')') >> OP('{') >> Body_F >> OP('}');
	Monad<Parser>* ELSE = Keyword_F('ELSE') >> Optional(OP('{')) >> Body_F >> Optional(OP('}'));
	Monad<Parser>* FOR = Keyword_F('FOR') >> OP('(') >> Expression_F >> OP(')') >> OP('{') >> Body_F >> OP('}');
	Monad<Parser>* FUNCTION = Type >> Type_F >> Identify_F >> OP('(') >> Arg_List_F >> OP(')') >> OP('{') >> Body_F >> OP('}');
	Monad<Parser>* CLASS = Keyword_F('CLASS') >> Identify_F >> OP('{') >> Body_F >> OP('}'); 
	cout << parserS->val->id << endl;
	//wcout << TS(val) << endl;
	getchar();
	return 0;
}
