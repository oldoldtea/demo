#include<iostream>
class A{
    int val;
public:
    A(int val):val(val){
        std::cout<<"A 构造:"<<val<<std::endl;
    }
    A(const A&){
        std::cout<<"A 构造"<<std::endl;
    }
    A(A&&){
        std::cout<<"A 构造"<<std::endl;
    }
    A& operator=(const A&){
        std::cout<<"A 构造"<<std::endl;
        return *this;
    }
};

struct B{
    A a={6};
    B():a({8}){
    }
};
int main(){
    B b;
}