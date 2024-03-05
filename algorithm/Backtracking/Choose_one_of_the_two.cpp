#include<iostream>
#include<vector>
using namespace std;
//二选一，应用情景数据量较小，时间复杂度是2^n
//应用情景1，对vec中数据加上+/-符号使和等于target并返回数量
int func1(vector<int>&vec,int target){
    int res=0;
    function<void(int,int)>fun=[&](int target,int index){
        if(index<vec.size()){
            if(index==vec.size()-1){
                if(target==-vec[index]) res++;
                if(target==vec[index]) res++;
            }
            fun(target-vec[index],index+1);
            fun(target+vec[index],index+1);
        }
    };
    return res;
}
int main(){

}