#include<iostream>

template<class,class>
constexpr bool same=false;

template<class T>
constexpr bool same<T,T> =true ;
template<typename T> concept limit=same<T,char>;
template<typename T,int> concept limit=same<T,char>;
template<limit T> void fun(T) {std::cout<<"char";}

int main(){
    fun('a');
}