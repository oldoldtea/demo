#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
//岛屿数量，思路遍历时遇到岛屿直接深度优先沉没掉，沉没岛屿的数量遍历可得
int func1(vector<vector<int>>&grid){
    int n=grid.size(),m=grid[0].size();
    function<bool(int,int)>fun=[&](int r,int c){
        if(r<0||c<0||r==n||c==m||grid[r][c]) return false;
        grid[r][c]=1;
        bool f1=fun(r+1,c);
        bool f2=fun(r-1,c);
        bool f3=fun(r,c+1);
        bool f4=fun(r,c-1);
        return r==0||c==0||r==n-1||c==m-1||f1||f2||f3||f4;
    };
    int res=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!grid[i][j]){
                res+=!fun(i,j);
            }
        }
    }
    return res;
}

//图形问题，求内部最大矩形，借助unordered_set存储每次遍历的行号和列号出现的行数乘列数等于遍历的数量时就可以证明这个是一个矩形
pair<int,int> func2(vector<vector<int>>&vec){
    int n=vec.size(),m=vec[0].size();
    unordered_set<int>sr,sc;
    int cnt=0;
    int max_is=0;
    pair<int,int> res=0;
    function<void(int,int)>fun=[&](int r,int c){
        sr.insert(r);sc.insert(c);
        if(sr.size()*sc.size()==cnt&&cnt>max_is){
            max_is=cnt;
            res=pair<int,int>{(int)sr.size,(int)sc.size()}; 
        } 
        vec[r][c]=1;//沉没岛屿思想
        cnt++;
        for(auto&i:vector<pair<int,int>>{{1,0},{0,1},{-1,0},{0,-1}}){
            int R=r+i.first,C=c+i.second;
            if(R>=0&&C>=0&&R<n&&C<m&&!vec[R][C]){
                fun(R,C);
            }
        }
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vec[i][j]) fun(i,j);
        }
    }
    return res;
}

//子矩形问题，给一个二维数组问有多少矩形
int main(){

}