#include<iostream>
#include<vector>
#include<functional>
using namespace std;

/*组合，数组内容：1 2 3
1 2 3
1 2
1 3
1
2 3
2
3
*/
vector<int>tmp;
vector<vector<int>>arr;
void func1(vector<int>&vec,int index){
    for(int i=index;i<vec.size();i++){
        if(i>index&&vec[i]==vec[i-1]) continue;//去重，i>index说明i前的值已经回溯掉了，此时如果相等需要跳过避免重复,去重的前提是相同元素都挨着
        tmp.push_back(vec[i]);
        func1(vec,i+1);
        tmp.pop_back();
    }
    arr.push_back(tmp);//放末尾是为了保证1xxx这种情况可以被添加进来，别的情况因为index==vec.size()也会被添加进来
}
/*全排列，数组内容：123，去重的话和组合方法一样
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 2 1 
3 1 2
*/
void func2(vector<int>&vec,int index){//不去重版本
    if(vec.size()==index)arr.push_back(vec);
    for(int i=index;i<vec.size();i++){
        swap(vec[i],vec[index]);
        func2(vec,index+1);
        swap(vec[i],vec[index]);
    }
}

void func2_demo(vector<int>&vec){//去重版本
    vector<bool>vis(vec.size(),false);//bitset
    function<void(int)>fun=[&](int index){
        if(index==vec.size()) {
            arr.emplace_back(tmp);
            return;//必须return否则越界
        }
        for(int i=0;i<vec.size();i++){
            if(vis[i]||(i&&vec[i]==vec[i-1]&&!vis[i-1])) continue;
            vis[i]=true;
            tmp.push_back(vec[i]);
            fun(index+1);
            vis[i]=false;
            tmp.pop_back();
        }
    };
    fun(0);
}
/*组合，位运算
*/
void func3(vector<int>&vec){
    int n=vec.size();
    //sort(vec.begin(),vec.end());
    for(int i=1;i<(1<<n);i++){
        tmp.clear();
        bool b=true;
        for(int j=0;j<n;j++){
            if(i&(1<<j)){
                if(j&&!(i&(1<<(j-1)))&&vec[j]==vec[j-1]){
                    b=false;
                    break;
                }
                tmp.push_back(vec[j]);
            } 
        }
        if(b) arr.emplace_back(move(tmp));
    }
}

void test(){
    for(auto&it:arr){
        for(auto i:it){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}
int main(){
    vector<int>vec{1,2,2};
    func2_demo(vec);
    test();
}