#include<iostream>
#include<vector>

using namespace std;

//参数中vec，n行n列，vec[i][j]表示i到j的距离是vec[i][j],到不了的位置距离是INT_MAX,cur表示初始的点
//思路，动态规划思想，创建一个数组用于存储[1,n]到初始节点的距离，
//每次从中选择未确定为最短的点中取最短的那个，将他确定为最短的，因为就算是绕路也没有比他更短的
//然后从这个点向后延展dis[j]=min(dis[j],vec[mi][j]+dis[mi]);更新最短路径后
//要求每段距离都为正整数
vector<int> fun(vector<vector<int>>&vec,int cur){
    int n=vec.size();
    vector<int>dis(n,INT_MAX);
    vector<bool>check(n,false);
    dis[cur]=0;
    for(int i=0;i<n;i++){
        int mv=INT_MAX,mi=cur;
        for(int j=0;j<n;j++){
            if(dis[j]<mv&&!check[j]){
                mv=dis[j];
                mi=j;
            }
        }
        check[mi]=true;
        for(int j=0;j<n;j++){
            if(vec[mi][j]!=INT_MAX){
                dis[j]=min(dis[j],vec[mi][j]+dis[mi]);
            }
        }
    }
    return dis;
}

int main(){}