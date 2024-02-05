#include <iostream>
#include <stdexcept>


template <typename T>
class MySharedPtr;

template <typename T>
class MyWeakPtr;

template <typename T>
class MySharedPtr {
private:
    T* ptr;
    int* refCount;
    int* weakCount;

public:
    explicit MySharedPtr(T* p = nullptr) : ptr(p), refCount(new int(1)), weakCount(new int(0)) {}

    MySharedPtr(const MySharedPtr& other) : ptr(other.ptr), refCount(other.refCount), weakCount(other.weakCount) {
        (*refCount)++;
    }

    ~MySharedPtr() {
        release();
    }

    int use_count() const {
        return (refCount ? *refCount : 0);
    }

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    MyWeakPtr<T> weak_ptr() {
        (*weakCount)++;
        return MyWeakPtr<T>(this->ptr, this->refCount, this->weakCount);
    }

    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            weakCount = other.weakCount;
            (*refCount)++;
        }
        return *this;
    }

private:
    void release() {
        if (refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                delete ptr;
                delete refCount;
                if (*weakCount == 0) {
                    delete weakCount;
                }
            }
        }
    }

    friend class MyWeakPtr<T>;
};

template <typename T>
class MyWeakPtr {
private:
    T* ptr;
    int* refCount;
    int* weakCount;

public:
    MyWeakPtr() : ptr(nullptr), refCount(nullptr), weakCount(nullptr) {}

    MyWeakPtr(T* p, int* rc, int* wc) : ptr(p), refCount(rc), weakCount(wc) {}

    MyWeakPtr(const MyWeakPtr& other) : ptr(other.ptr), refCount(other.refCount), weakCount(other.weakCount) {
        (*weakCount)++;
    }

    ~MyWeakPtr() {
        release();
    }

    T* operator->() const {
        if (expired()) {
            throw std::runtime_error("Expired weak_ptr");
        }
        return ptr;
    }

    MySharedPtr<T> lock() {
        if (expired()) {
            return MySharedPtr<T>();
        }
        (*refCount)++;
        return MySharedPtr<T>(ptr, refCount, weakCount);
    }

    MyWeakPtr& operator=(const MyWeakPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            weakCount = other.weakCount;
            (*weakCount)++;
        }
        return *this;
    }

    bool expired() const {
        return (refCount == nullptr || *refCount == 0);
    }

private:
    void release() {
        if (weakCount) {
            (*weakCount)--;
            if (*weakCount == 0) {
                delete weakCount;
            }
        }
    }
};

class B;
class A{
public:
    MySharedPtr<B>aptr;
};
class B{
public:
    MyWeakPtr<A>bptr;
    ~B(){
        std::cout<<"ok";
    }
};




int main(){
    using namespace std;
    MySharedPtr<A>a{new A()};
    MySharedPtr<B>b{new B()};
    a->aptr=b;
    b->bptr=a.weak_ptr();
}