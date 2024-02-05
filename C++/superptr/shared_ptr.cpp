#include <iostream>
#include <string>

template<typename T>
class shared_ptr{
    T*ptr;
    int* cnt;
public:
    shared_ptr(T*p=nullptr):ptr(p),cnt(new int(1)){}
    shared_ptr(const shared_ptr&other) noexcept:ptr(other.ptr),cnt(other.cnt){
        (*cnt)++;
    }
    shared_ptr& operator=(const shared_ptr&other) noexcept{
        if(this!=&other){
            release();
            this->ptr=other.ptr;
            this->cnt=other.cnt;
            (*cnt)++;
        }
        return *this;
    }
    T*get()const{
        return ptr;
    }
    T& operator*() const{
        return *ptr;
    }
    T* operator->() const{
        return ptr;
    }
    explicit operator bool() const{
        return ptr!=nullptr;
    }
    ~unique_ptr(){
        release();
    }
    void release(){
        if(cnt&&--(*cnt)==0){
            delete cnt;
            delete ptr;
        }
        ptr=nullptr;
        cnt=nullptr;
    }
};



/*
shared_ptr指针的特性：
1.可以有多个指针对象指向一块地址
2.使用一块堆区空间维护一块地址被指向的次数
3.当指向一个地址的指针数量变为0时清除这块空间

问题：可能出现循环引用的问题
例如：
class B;
class A{
public:
    shared_ptr<B>aptr;
};
class B{
public:
    shared_ptr<A>bptr;
};
shared_ptr<A>a=new shared_ptr<A>;
shared_ptr<B>b=new shared_ptr<B>;

a->aptr=b;
b->bptr=a;
析构时会进入递归状态，为处理这种情况引入了weak_ptr
*/