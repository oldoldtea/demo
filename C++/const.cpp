#include<iostream>
using namespace std;

const int t1=1;
struct A{
    const int t2=1;
};
void test1(const int&t){
    int*T=(int*)&t;
    *T=100;
    cout<<t;
}
int test2(const int&t){
    return t;
}
int main(){
    const int t3=1;//t3的初值被存储进了寄存器
    volatile const int t4=1;//t4被volatile修饰存储的值不能存储进寄存器
    A a;//A的常成员变量不会存储在寄存器中
    test1(t3);//输出100，修改了t3内容
    cout<<t3<<*(&t3)<<test2(t3)<<endl;
    //输出1，1，100，对t3的访问直接走寄存器
    test1(t4);//输出100，修改了t3内容
    cout<<t4<<*(&t4)<<test2(t4)<<endl;
    //输出100，100，100
    test1(a.t2);//输出100
    cout<<a.t2<<*(&a.t2)<<test2(a.t2)<<endl;
    //输出100，100，100
    /*
    test1(t1);段错误，因为t1是全局初始化过的常量存储在data段，只读
    */
}

/*
总结：const修饰的局部变量如果被使用，编译期间它的初值会被存储在寄存器中
引用传参是const时，const关键字会失去效果，变量不会存储在寄存器中，对地址内数据的修改会改变引用的值
需要注意volatile关键字的使用
编写代码时最好注意避免不必要的指针操作
*/