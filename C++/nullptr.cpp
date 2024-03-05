#include<iostream>

class null {
public:
	template<class Base>
	constexpr operator Base* ()noexcept {
		return static_cast<Base*>(0);
	}
};

#define nullptr_  static_cast<null&&>(null())

int main(){
    nullptr;
}