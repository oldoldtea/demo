#include<iostream>
int main(){
	int x=6,y=8;
	auto fun=[&]{return x+y;};
	int z=fun();
}