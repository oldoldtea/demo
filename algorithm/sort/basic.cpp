#include<iostream>
#include<vector>
#include<functional>
using namespace std;

void test(vector<int>&vec){
    for(int i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
}

//快速排序 时间复杂度O（nlog n）- O（n^2） 空间复杂度 O（1） 不稳定
void func(vector<int>&nums,int start,int end){
    if(start>=end) return;
    int s=start-1,e=end+1;
    int val=nums[start];//每轮遍历的标记点，决定了快排的性能，可以用五分中位数优化
    int index=start;
    while (index<e)
    {
        if(nums[index]==val){
            index++;
        }
        else if(nums[index]<val){
            swap(nums[index],nums[++s]);
            index++;
        }
        else swap(nums[index],nums[--e]);
    }
    func(nums,start,s);
    func(nums,e,end);
}
//堆排序 时间复杂度O（n log n） 空间复杂度 O（1） 不稳定
void func1(vector<int>&nums){
    function<void(int,int)>merge=[&](int start,int end){
        int father=start;
        int child=start*2+1;
        while(child<=end){
            if(child+1<=end&&nums[child+1]>nums[child]) child++;
            if(nums[child]>nums[father]){
                swap(nums[child],nums[father]);
                father=child;
                child=2*father+1;
            }
            else break;
        }
    };
    int n=nums.size();
    for(int i=n/2-1;i>=0;i--){
        merge(i,n-1);
    }
    for(int i=n-1;i>=0;i--){
        swap(nums[i],nums[0]);
        merge(0,i-1);
    }
}
//归并排序 时间复杂度O（n log n） 空间复杂度O（n） 稳定
void func2(vector<int>&nums,int start,int end){
    test(nums);
    if(start>=end) return;
    int mid=(start+end)/2;
    func2(nums,start,mid);
    func2(nums,mid+1,end);
    vector<int>tmp(end-start+1);
    int start1=start,start2=mid+1;
    int index=0;
    while(start1<=mid||start2<=end){
        int val1=start1<=mid?nums[start1]:INT32_MAX;
        int val2=start2<=end?nums[start2]:INT32_MAX;
        if(val1>val2){
            tmp[index++]=nums[start2++];
        }
        else tmp[index++]=nums[start1++];
    }
    for(int i=start;i<=end;i++) nums[i]=tmp[i-start];
}
//插入排序 时间复杂度 O（n^2） 空间复杂度 O(1) 不稳定
void func3(vector<int>&nums){
    int n=nums.size();
    for(int i=1;i<n;i++){
        int val=nums[i],j=i-1;
        while (j>=0&&nums[j]>val) nums[j+1]=nums[j--];
        nums[j+1]=val;
    }
}
//冒泡排序 时间复杂度 O（n^2）空间复杂度 O（1）不稳定
void func4(vector<int>&nums){
    int n=nums.size();
    for(int i=0;i<n-1;i++){
        bool flag=true;
        for(int j=i+1;j<n;j++){
            if(nums[i]>nums[j]){
                flag=false;
                swap(nums[i],nums[j]);
            } 
        }
        if(flag) break;
    }
}
//选择排序 时间复杂度 O（n^2） 空间复杂度 O（1） 
void func5(vector<int>&nums){
    int n=nums.size();
    for(int i=1;i<n;i++){
        int index=0;
        for(int j=1;j<=n-i;j++){
            if(nums[j]>nums[index]) index=j;
        }
        swap(nums[index],nums[n-i]);
    }
}
int main(){
    vector<int>vec{5,6,3,7,8,9};
    func1(vec);
    test(vec);
}