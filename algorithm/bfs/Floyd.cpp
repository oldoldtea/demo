#include<iostream>
#include<vector>
using namespace std;


/*
处理多对多最短路径问题，思路：最短路径的出现一定是需要绕路或者不绕路，
对绕路遍历中间节点然后和直达的路径比较一下然后就可以得到任意起点和终点下的最短路径
*/
vector<vector<int>> fun(vector<vector<int>>&g,int cur){
    int n=g.size();
    vector<vector<int>>res(n,vector<int>(n,INT_MAX));
    for(int i=0;i<n;i++){//控制中转点
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                if(g[j][k]>g[j][i]+g[i][k]){
                    g[j][k]=g[j][i]+g[i][k];
                }
            }
        }
    }
    return res;
}

int main(){}