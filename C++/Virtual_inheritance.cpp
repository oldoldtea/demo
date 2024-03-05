#include<iostream>
using namespace std;


/*虚继承解决了对同一基类多次继承产生的二义性问题，同时减少了不必要的基类创建
https://www.cnblogs.com/j1nux/p/16742817.html

class A{
    public:
    int a=1;
};
class B:public A{};
class C:public A{};

class D:public B,public C{

};

/*
虚继承原理是创建一个在各自的类实例化的时候创建一个虚表内置偏移量（虚表指针到父类数据地址的距离）
虚继承是保证只有一个间接父类
虚继承需要继承时都使用virtual声明

*/
class A{
public:
    int a=1;
};
class B:virtual public A{};
class C:virtual public A{};
class D:public B,public C{};


//注意对齐问题
/*class A{
public:
    int a=1;
    virtual void fun1(){
        cout<<"A";
    }
};
class B{
public:
    int a=2;
    virtual void fun2(){
        cout<<"B";
    }
};
class D{
public:
    int a=3;
    virtual void fun3(){}
};
class C:virtual public A,virtual public B,virtual public D{
public:
};
*/

int main(){
    D d;
    cout<<d.a;
    //C c;
    //cout<<sizeof(c)<<sizeof(A);
    //for(int i=0;i<=sizeof(c)/4;i++)cout<< *(((int*)&c)+i)<<endl;
}