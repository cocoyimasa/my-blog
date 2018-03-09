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
	Monad<Parser>* parserS = pm >> f >> g >> h >> m >> end; //做的基础设施就是为了这样串起来
	Monad<Parser>* Binary_F = Expression >> (OP('||') | OP('&&') |) >> Expression;
	Monad<Parser> Unary = (OP('+')|OP('-')|OP('::'))Expression;
	Monad<Parser>* Expression = Identify_F | Unary_F | Binary_F | Ternary_F;
	Monad<Parser>* parserS = pm >> f >> g >> h >> m >> end; //做的基础设施就是为了这样串起来
	Monad<Parser>* IF = Keyword_F('IF') >> OP('(') >> Expression_F >> OP(')') >> OP('{') >> Body_F >> OP('}');
	Monad<Parser>* ELSE = Keyword_F('ELSE') >> Optional(OP('{')) >> Body_F >> Optional(OP('}'));
	Monad<Parser>* FOR = Keyword_F('FOR') >> OP('(') >> Expression_F >> OP(')') >> OP('{') >> Body_F >> OP('}');
	Monad<Parser>* FUNCTION = Type_F >> Identify_F >> OP('(') >> Arg_List_F >> OP(')') >> OP('{') >> Body_F >> OP('}');
	cout << parserS->val->id << endl;
	//wcout << TS(val) << endl;
	getchar();
	return 0;
}
