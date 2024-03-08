#include<iostream>
#include<vector>
using namespace std;
//Z函数，返回最长匹配前/后缀，比如abab它的最长前后缀是2，abc是0
void init(vector<int>&nums,string& t){
	for(int i=1,j=0;i<t.size();i++){
		while(j&&nums[i]!=nums[j]){
			j=nums[j-1];
		}
		if(nums[i]==nums[j]) j++;
		nums[i]=j;
	}
}
//kmp算法主体，借助z函数初始化不同位置下匹配的前后缀减少比较次数
int find(string s,string t){
	if(t.empty()) return -1;
	vector<int>tmp(t.size(),0);
	init(tmp,t);
	for(int i=0,j=0;i<s.size();i++){
		while(j&&s[i]!=t[j]){
			j=tmp[j-1];
		}
		if(s[i]==t[j]) j++;
		if(j==t.size()) return i-t.size()+1;
	}
	return -1;
}


int main(){
}