#include<iostream>
#include<vector>
#include<functional>
#include<unordered_map>
#include<unordered_set>
using namespace std;
//0-1背包，背包大小target，占用容积vec[i][0]，可以带来的利益是vec[i][1]
//一件物品只能取一次,先遍历物品然后遍历背包更新不同容积下最大的利益
int func(vector<vector<int>>&vec,int target){
    vector<int>dp(target+1,0);
    for(int i=0;i<vec.size();i++){
        for(int w=target;w>=vec[i][0];w--){
            dp[w]=max(dp[w-vec[i][0]]+vec[i][1],dp[w]);
        }
    }
    return dp[w];
}
//完全背包,与0-1背包相比差别在于物品可以多次选择了
//思路和0-1背包差不多，只不过遍历背包容积时从低到高，每次更新时之前都是包含当前物品最优
int func1(vector<vector<int>>&vec,int target){
    vector<int>dp(target+1,0);
    for(int i=0;i<vec.size();i++){
        for(int w=vec[i][0];w<=target;w++){
            dp[w]=max(dp[w-vec[i][0]]+vec[i][1],dp[w]);
        }
    }
    return dp[w];
}

//多重背包，每种物品有vec[i][j][2]个
//思路1，二进制商品拆分（比如：111可以组合成1-6任意数字），转化为0-1背包问题
int func2(vector<vector<int>>&vec,int target){
    int n=vec.size();
    vector<pair<int,int>>goods;
    for(auto&i:vec){
        for(int j=1;j<=i[2];i*=2){
            i[2]=i[2]-j;
            goods.push_back({i[0]*j,i[1]*j});
        }
        goods.push_back({i[2]*i[0],i[2]*i[1]});
    }
    vector<int>dp(target+1,0);
    for(int i=0;i<goods.size();i++){
        for(int j=target;j>=goods[i].first;j--){
            dp[j]=max(dp[j],dp[j-goods[i].first]+goods[i].second);
        }
    }
    return dp[target];
}

//思路2 添加物品数量层遍历
int func3(vector<vector<int>>&vec,int target){
    vector<int>dp(target+1,0);
    for(int i=0;i<vec.size();i++){
        for(int j=target;j>=vec[i][0];j--){
            for(int k=1;k*vec[i][0]<j&&k<=vec[i][2];k++){
                dp[j]=max(dp[j],dp[j-k*vec[i][0]]+k*vec[i][1]);
            }
        }
    }
    return dp[target];
}
//混合背包，背包中的物品可以有无限个或者有限个
//vec[i][0]重量，vec[i][1]价值，vec[i][2]数量
int func4(vector<vector<int>>&vec,int target){
    vector<int>dp(target+1,0);
    for(int i=0;i<vec.size();i++){
        if(vec[i][2]==0){
            for(int j=vec[i][0];j<=target;j++){
                dp[j]=max(dp[j],dp[j-vec[i][0]]+vec[i][1]);
            }
        }
        else {
            for(int j=target;j>=vec[i][0];j--){
                for(int k=1;k*vec[i][0]<j&&k<=vec[i][2];k++){
                    dp[j]=max(dp[j],dp[j-k*vec[i][0]]+k*vec[i][1]);
                }
            }
        }
    }
    return dp[target];
}
//分组背包
//商品分组，每组最多只能选一个，vec[i][k][0]重量，vec[i][k][1]价值
int func5(vector<vector<vector<int>>>&vec,int target){
    vector<int>dp(target+1,0);
    for(int i=0;i<vec.size();i++){
        for(int j=target;j>=0;j--){//遍历背包容积
            for(int k=0;k<vec[i].size();k++){//遍历商品组内商品
                if(j>=vec[i][k][0]) dp[j]=max(dp[j],dp[j-vec[i][k][0]]+vec[i][k][1]);
            }
        }
    }
    return dp[target];
}
//二维背包
//约束条件增加，vec[i][0]价值，vec[i][1]是第一个约束条件，vec[i][2]是第二个约束条件
int func6(vector<vector<int>>&vec,int target1,int target2){
    vector<vector<int>>dp(target1+1,vector<int>(target2+1,0));
    for(int i=0;i<vec.size();i++){
        for(int j=target1;j>=vec[i][1];j--){
            for(int k=target2;k>=vec[i][2];k--){
                dp[j][k]=max(dp[j][k],dp[j-vec[i][1]][k-vec[i][2]]+vec[i][0]);
            }
        }
    }
    return dp[target1][target2];
}
//树状背包
//买一件物品前必须买另一件
//map键值是编号，first负重，second价值，买d[i][0]前必须买d[i][1],d[i][1]=0时表示没有依赖
//思路，回溯思想自底向上遍历，每一层子树作为一个临时的商品组，根节点必须买，根节点买不了时更新为0
//原理是把一棵树分为整合为前缀和组，实现起来保证每种情况更新到且在回溯前更新完即可
//注意更新的数据所在的层级
int func7(unordered_map<int,pair<int,int>>&map,vector<vector<int>>&d,int target){
    int n=map.size();
    vector<vector<int>>tree(n+1);
    vector<vector<int>>dp(n+1,vector<int>(target+1));
    for(auto i:d){
        tree[i[1]].push_back(i[0]);
    }
    function<void(int)>dfs=[&](int root){
        for(int i=0;i<tree[root].size();i++){//遍历商品组
            int son=tree[root][i];
            dfs(son);
            for(int j=target-map[root].first;j>=map[son].first;j--){//商品组内不应该包含根节点，所以需要保留
                for(int k=0;k<=j;k++){//对商品的抽象，直接抽象为了对应的大小，不存在时为0
                    dp[root][j]=max(dp[root][j],dp[root][j-k]+dp[son][k]);
                }
            }
        }
        for(int j=target;j>=map[root].first;j--)//根节点必须买 
            dp[root][j]=dp[root][j-map[root].first]+map[root].second;
        for(int j=0;j<map[root].first;j++) //根节点买不了的话g
            dp[root][j]=0;
    };
    dfs(0);
    return dp[0][target];
}

int main(){}