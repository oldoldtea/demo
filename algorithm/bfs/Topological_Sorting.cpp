#include<iostream>
#include<vector>

using namespace std;

//拓扑排序，广度遍历，遍历完一层遍历下一层
//vec依赖数组，选择vec[i][0]前必须选择vec[i][1]
//思路依赖计数为0时表示可以选取
void func(vector<vector<int>>&vec,int n){
    queue<int>que;
    vector<int>cnt(n);
    vector<vector<int>>m(n);
    for(auto& i:vec){
        m[i[1]].push_back(i[0]);
        cnt[i[0]]++;
    }
    for(int i=0;i<n;i++) if(!cnt[i]) que.push(i);
    while (!que.empty()){
        int size=que.size();
        while (size--){
            int fr=que.front();
            que.pop();
            for(int i:m[fr]){
                if(--cnt[i]==0){
                    que.push(i);
                }
            }   
        }
    }
}

int main(){
}