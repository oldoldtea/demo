#include<iostream>
#include<functional>
using namespace std;

/*
前缀树，高效的存储和搜索字符串
原理，将节点的索引作为存储的字符，然后就可以很好的将字符串的问题转化为树的问题，遍历时问题规模不断的变小
对某些问题记得标志是否是尾部
*/
struct tree{
    tree* node[26]={0};
    int end=0;
};

class Trie{
    tree*root;
public:
    Trie():root(new tree){}
    void insert(string& s){
        tree*cur=root;
        function<void(int)>fun=[&](int index){
            if(index==s.size()) return;
            if(!cur->node[s[index]-'a']) cur->node[s[index]-'a']=new tree;
            cur=cur->node[s[index]-'a'];
            if(index==s.size()-1) cur->end++;
            fun(index+1);
        };
        fun(0);
    }
    bool search(string& s){
        tree*cur=root;
        function<bool(int)>fun=[&](int index){
            if(index==s.size()) return true;
            if(!cur->node[s[index]-'a']) return static_cast<bool>(cur->end);
            cur=cur->node[s[index]-'a'];
            return fun(index+1);
        };
        return fun(0);
    }
    bool startwith(string& s){
        tree*cur=root;
        function<bool(int)>fun=[&](int index){
            if(index==s.size()) return true;
            if(!cur->node[s[index]-'a']) return false;
            cur=cur->node[s[index]-'a'];
            return fun(index+1);
        };
        return fun(0);
    }
};

int main(){
    string s="abc";
    Trie t;
    t.insert(s);
}