#include<iostream>
#include<vector>
using namespace std;
//跳台阶问题，当前在vec[0]，在i时可以跳vec[i]，能否到达(跳跃节点可能存在负数)
bool func(vector<int>&vec){
    int n=vec.size(),cur=0;
    if(!n||vec[0]>=n) return true;
    vector<bool>vis(n,false);
    vis[0]=true;
    while(cur<n-1){
        cur+=vec[cur];
        if(cur<0||vis[cur]) return false;
        vis[cur]=true;
    }
    return true;
}
//跳台阶问题，当前在0,每一次可以跳[0,vec[i]],问最少几步能到
void func1(vector<int>&vec){
    int n=vec.size();
    vector<int>step(n,INT_MAX);step[0]=0;
    for(int i=0;i<vec.size();i++){
        int next=i+vec[i];
        for(int j=i+1;j<=next&&j<n;j++){
            step[j]=min(step[j],step[i]+1);
        }
    }
    return step.back()==INT_MAX?-1:step.back();
}
//优化版本，贪心思想，每次在上一步落地前找出下一步最合适的落脚点，即一直保持能够在有限步数内走的最远
void func1_demo(vector<int>&vec){
    int n=vec.size();
    int last=0,cur=0,step=0;
    for (int i = 0; i < n-1; i++){//这里需要n-1的作用是避免刚好到n-1的情况下setp的++行为
        if(cur>=i){
            cur=max(cur,vec[i]+i);
            if(i==end){
                end=cur;
                step++;
            }
        }
    }
    return step;
}

int main(){}