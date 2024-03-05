#include<iostream>
#include<functional>
using namespace std;


struct tree{
    tree* node[26]={0};
    int end=0;
};

class Trie{
    tree*root;
public:
    Trie():tree(new tree){}
    void insert(string& s){
        function<void(int)>fun=[&,cur=root](int index){
            if(index==s.size()) return;
            if(!cur->node[s[index]-'a']) cur->node[s[index]-'a']=new tree;
            cur=cur->node[s[index]-'a'];
            if(index==s.size()-1) cur->end++;
            fun(index+1);
        };
        fun(0);
    }
    bool search(string& s){

    }
    bool startwith(string& s){

    }
}

int main(){
    string s="abc";
    Trie t;
    t.insert(s);
}