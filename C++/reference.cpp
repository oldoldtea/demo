//#include <iostream>
//using namespace std;

long long a=10;
/*
class A{
    long long&b=a;    
};
namespace v
{
    void fun(long long p){
        cout<<"值";
    }
}*/
void fun(long long*p){
    //cout<<"指针";
    *p=10;
}
void fun(long long&p){
    //cout<<"引用";
    p=10;
}
int main(){
    //v::fun(a);
    fun(a);
    fun(&a);
    //cout<<sizeof(A)<<sizeof(long long)<<sizeof(long long*);
    return 0;
}
/*
总结：引用的本质是一个指针