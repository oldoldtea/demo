#include <iostream>
#include <string>

template<typename T>
class unique_ptr{
    T*ptr;
public:
    unique_ptr(T*p=nullptr):ptr(p){}
    unique_ptr(unique_ptr&&other) noexcept:ptr(other.release()){
        other.ptr=nullptr;
    }
    unique_ptr& operator=(unique_ptr&&other) noexcept{
        if(other.ptr!=this->ptr){
            change(other.release());
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
        delete ptr;
        ptr=nullptr;
    }
    T*release(){
        T*tmp=this->ptr;
        this->ptr=nullptr;
        return tmp;
    }
    void change(T*cur=nullptr){
        if(cur!=ptr){
            delete ptr;
            ptr=cur;
        }
    }
    unique_ptr(const unique_ptr&)=delete;
    unique_ptr& operator=(const unique_ptr&)=delete;
};


/*测试*/

struct A
{
    int no=10;
    std::string str="test for unique_ptr";
    bool result=true;
};


int main(){
    A* a=new A;
    unique_ptr<A>ptr(a),tmp;
    std::cout<<ptr->str<<std::endl;
    tmp=ptr.release();
    if(!ptr.get()){
        std::cout<<(tmp->result?"true":"false")<<std::endl;
    }
}

/*
unique智能指针特性：
1.不能有多个对象指向一块内存
2.对象释放时内部指针指向地址也随之释放
3.对象内数据只能通过接口更改绑定
4.对象只能接收右值或者将亡值
*/