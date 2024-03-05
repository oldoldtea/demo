#include<iostream>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<mutiset>
#include<vector>
using namespace std;

//数据滚动，案例1求最长无相同字符区间长度
void func1(string&s){
    int res=0,tmp=-1;
        unordered_map<char,int>map;
        for(int i=0;i<s.size();i++){
            if(map.count(s[i])){
                tmp=max(tmp,map[s[i]]);
            }
            map[s[i]]=i;
            res=max(res,i-tmp);
        }
        return res;
}
//数据分类，案例2，字符串数组以各种字母出现的数量为基准归类
vector<vector<string>> func2(vector<string>& strs) {
    unordered_map<string,vector<string>>map;
    for(string& s:strs){
        string tmp(26,0);
        for(char ch:s){
            tmp[ch-'a']++;
        }
        map[tmp].emplace_back(move(s));
    }
    vector<vector<string>>res;
    for(auto&it:map){
        res.emplace_back(std::move(it.second));
    }
    return res;
}

int main(){
    
}