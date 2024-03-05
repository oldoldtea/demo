#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;


//模板，非递归版的广度优先遍历
//案例1，开锁的最快时间,题目链接：https://leetcode.cn/problems/open-the-lock/

void func(vector<string>&dead,string target){
    unordered_set<string>st(deadends.begin(),deadends.end());
    if(st.count("0000")) return -1;
    else if(target=="0000") return 0;
    queue<string>que;
    que.emplace("0000");
    for(int res=1;!que.empty();res++){
        for(int i=que.size();i;i--){
            string str=que.front();
            que.pop();
            for(int i=0;i<4;i++){
                char s=str[i];
                for(int pp:{1,-1}){
                    str[i]=(s-'0'+pp+10)%10+'0';
                    if(str==target) return res;
                    if(!st.count(str)){
                        st.insert(str);
                        que.emplace(str);
                    }
                }
                str[i]=s;
            }
        }
    }
    return -1;
}


int main(){}