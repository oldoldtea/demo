#include<iostream>
#include <cstring>
struct A {
	char* ptr;
	A():ptr(new char[4096]) {}
	A(const A& other):ptr(new char[4096]) {
		std::cout << "copy" << std::endl;
		memcpy(ptr, other.ptr, 4096);
	}
	A(A&&other){
		std::cout << "move" << std::endl;
		ptr=other.ptr;
		other.ptr=nullptr;
	}
	~A() {
		if (ptr) delete[]ptr;
	}
};

A make_A() {
    return A();
}

template<class T>
void show_type(T&& t){
    std::cout<<typeid(t).name()<<std::endl;
    t.ptr=nullptr;
}
template<class T>
void g(T&& t){
	show_type(std::move(t));
}

template<class T>
struct type{
    using t=T;
};
template<class T>
using ty = typename type<T>::t;
template <class>
const bool is_lvalue_reference_v = false; // determine whether type argument is an lvalue reference

template <class _Ty>
const bool is_lvalue_reference_v<_Ty&> = true;

template<class T>
T&& gg(ty<T>&&p){
    static_assert(!is_lvalue_reference_v<T>, "bad forward call");
    std::cout<<"ok";
    return static_cast<T&&>(p);
}

int main(){
    A a;
    A&& b=A();
    gg<A&>(A());
}
