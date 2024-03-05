#include<iostream>
#include<stdlib.h>
#include <cstring>
struct A {
	char* ptr;
	A():ptr(new char[4096]) {}
	A(const A& other):ptr(new char[4096]) {
		std::cout << "copy start" << std::endl;
		memcpy(ptr, other.ptr, 4096);
	}
	A(A&&other){
		std::cout << "move start" << std::endl;
		ptr=other.ptr;
		other.ptr=nullptr;
	}
	~A() {
		if (ptr) delete[]ptr;
	}
};
A get_A(const A& a) {
	return a;
}
A make_A() {
	A a;
	return get_A(a);
}

struct B{
	char *ptr;
	B():ptr(new char[10]){}
	B(B&&other){
		std::cout << "move start" << std::endl;
		ptr=other.ptr;
		other.ptr=nullptr;
	}
};
struct C{
	char *ptr;
	C():ptr(new char[10]){}
	C(C&&){
		std::cout<<"move"<<std::endl;
	}
	C(const C&){
		std::cout<<"copy"<<std::endl;
	}
};
template<class T>
void show_type(T t){
}
template<class T>
void g(T&&t){
	show_type(static_cast<T&&>(t));
}
std::string get_val(){
	return "hhh";
}


int main(){
	//g(get_val());
	//std::string s="hhh";
	C c;
	g(c);
}
/*int main() {
	//A a = make_A();
	B b;
	B&& i=B();
	B c=i;
	if(!b.ptr) std::cout<<"move success"<<std::endl;
}*/