#include<iostream>
#include <cstring>
using namespace std;

class A{
    char*ptr;
public:
    A():ptr(new char[100]){
        ptr[1]='a';
    }
    A(const A&other):ptr(new char[100]){
        //*(this->ptr)=*(other.ptr);
        
        memcpy(ptr,other.ptr,100);cout<<ptr[1];
    }
    A(A&&other){
        ptr=other.ptr;
        other.ptr=nullptr;
        cout<<"移动构造";
    }
    A& operator=(A&&other){
        ptr=other.ptr;
        other.ptr=nullptr;
        cout<<"移动赋值";
        return *this;
    }
    ~A(){
        delete[] ptr;
    }
};


template<class T>
constexpr T&& move(T&& t)noexcept{
    return static_cast<T&&>(t);
}


int main(){
    A a;
    A b(a);
    //b=std::move(a);
}