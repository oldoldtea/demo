#include<iostream>
#include<vector>
#include<unordered_set>
#include<queue>
using namespace std;


//模板，非递归版的广度优先遍历
//案例1，开锁的最快时间,题目链接：https://leetcode.cn/problems/open-the-lock/
//特点利用队列可以控制遍历轮次，还可以控制节点加入，控制节点的加入时需要考虑条件的设置

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

//广度优先求最短路径问题
//不加权，有障碍物
int func1(vector<vector<int>>&map){
    int n=map.size(),m=map[0].size(),res=0;
    vector<pair<int,int>>d{{0,1},{0,-1},{1,0},{-1,0}};//定义方向
    unordered_set<int>set;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!map[i][j]) set.insert((i<<10)+j);
        }
    }
    queue<pair<int,int>>que;
    que.push({0,0});
    set.insert(0);
    while (!que.empty())
    {
        int size=que.size();res++;
        while (size--)
        {
            auto[r,c]=que.front();
            que.pop();
            for(auto&it:d){
                int R=r+it.first;
                int C=c+it.second;
                if(R>=0&&C>=0&&R<n&&C<m&&!set.count((R<<10)+C)){
                    if(R==n-1&&C==m-1) return res;
                    que.push({R,C});
                    set.insert((R<<10)+C);
                }
            }
        }
    }
    return -1;
}
//不加权，有障碍物，可以清除k个障碍物


//加权无障碍

//加权有障碍



int main(){}