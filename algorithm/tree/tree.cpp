#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>
#include<queue>
#include<unordered_map>
using namespace std;
struct tree
{
    int val;
    tree*left,*right;
    tree(int val,tree*left,tree*right):val(val),left(left),right(right){}
};
//递归创建搜索树
tree*func(vector<int>&vec){
    int n=vec.size();
    sort(vec.begin(),vec.end());
    function<tree*(int,int)>fun=[&](int start,int end)->tree*{
        if(start>end) return nullptr;
        int mid=(start+end)/2;
        tree*root=new tree(vec[mid],nullptr,nullptr);
        root->left=fun(start,mid-1);
        root->right=fun(mid+1,end);
        return root;
    };
    return fun(0,n-1);
}

//递归先序、中序、后序遍历
void func1(tree*root){
    if(!root) return;
    
    if(root->left) func1(root->left);
    if(root->right) func1(root->right);cout<<root->val;
}
//非递归先序
void func2(tree*root){
    if(!root) return;
    stack<tree*>stk;
    stk.push(root);
    while(!stk.empty()){
        tree*cur=stk.top();
        cout<<cur->val;
        stk.pop();
        if(cur->right) stk.push(cur->right);
        if(cur->left) stk.push(cur->left);
        
    }
}
//非递归中序
void func3(tree*root){
    if(!root) return;
    stack<tree*>stk;
    while(root!=nullptr||!stk.empty()){
        while(root){
            stk.push(root);
            root=root->left;
        }
        root=stk.top();
        stk.pop();
        cout<<root->val;
        root=root->right;
    }
}

//非递归后序
void func4(tree*root){
    if(!root) return;
    stack<tree*>stk;
    tree*pre=nullptr;
    while(root||!stk.empty()){
        while(root){
            stk.emplace(root);
            root=root->left;
        }
        root=stk.top();
        stk.pop();
        if(!root->right||root->right==pre){
            cout<<root->val;
            pre=root;
            root=nullptr;
        }
        else {
            stk.push(root);
            root=root->right;
        }
    }
}

//先序中序构建二叉树,分治思想，中序遍历时索引前的是该节点的右子树，左边在左子树，利用这一点可以不断向下分割左右子树，就可以搭建
tree*build(vector<int>&pre,vector<int>&ino){
    unordered_map<int,int>map;
    for(int i=0;i<ino.size();i++) map[ino[i]]=i;
    int count=0;
    function<tree*(int,int)>fun=[&](int left,int right)->tree*{
        if(left>right) return nullptr;
        int val=pre[count++];
        tree*root=new tree(val,
        fun(left,map[val]-1),
        fun(map[val]+1,right)
        );
        return root;
    };
    return fun(0,pre.size()-1);
}
//中序后序构建二叉树,和先序中序遍历构建的原理一致
tree*build1(vector<int>&ino,vector<int>&post){
    unordered_map<int,int>map;
    for(int i=0;i<ino.size();i++) map[ino[i]]=i;
    int count=ino.size()-1;
    function<tree*(int,int)>fun=[&](int left,int right)->tree*{
        if(left>right) return nullptr;
        int val=post[count--];
        tree*root=new tree(val,nullptr,nullptr);
        root->right=fun(map[val]+1,right);
        root->left=fun(left,map[val]-1);
        return root;
    };
    return fun(0,ino.size()-1);
}
//先序后序构建二叉树
tree*build2(vector<int>&pre,vector<int>&post){
    int preindex=0,postindex=0;
    function<tree*()>fun=[&]()->tree*{
        tree* root=new tree(pre[preindex++],nullptr,nullptr);
        if(post[postindex]!=root->val) root->left=fun();
        if(post[postindex]!=root->val) root->right=fun();
        postindex++;
        return root;
    };
    return fun();
}

//先序创建
tree*pref(vector<int>&pre,int index=0){
    if(index>=pre.size()||pre[index]=-1) return nullptr;
    tree*root=new tree(pre[index],pref(pre,++index),pref(pre,++index));
    return root;
}

int main(){
    vector<int>d{1,2,3,4,5,6};
    tree*cur=func(d);
    func4(cur);
    cout<<endl;
    func1(cur);
}