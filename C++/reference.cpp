#include <iostream>
using namespace std;

long long a=10;

class A{
    long long&b=a;    
};
namespace v
{
    void fun(long long p){
        cout<<"值";
    }
}
void fun(long long*p){
    cout<<"指针";
}
void fun(long long&p){
    cout<<"引用";
}
int main(){
    v::fun(a);
    fun(a);
    fun(&a);
    cout<<sizeof(A)<<sizeof(long long)<<sizeof(long long*);
    return 0;
}
/*
总结：引用的本质是一个指针
指针传递和引用传递的传参过程的汇编代码是一样的，引用是对指针的一种包装
引用不是简单的通过在符号表中添加变量名和地址的对应关系（符号表中只能是一对一的关系）
引用的作用是将指针变量转化为所指向对象，int* a=&b转化为 int& a=b，&的作用是区分int和int引用 
https://godbolt.org/
*/