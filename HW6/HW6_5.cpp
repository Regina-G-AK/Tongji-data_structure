#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums)
{
    vector<vector<int>> result;
    for(int i=0;i<nums.size();i++){
        if(i>0&&nums[i]==nums[i-1]) 
            continue;
        int l=i+1;
        int r=nums.size()-1;
        while(l<r){
            int sum=nums[i]+nums[l]+nums[r];
            if(sum==0){
                result.push_back({nums[i],nums[l],nums[r]});
                while(l<r&&nums[l]==nums[l+1]) 
                    l++;
                while(l<r&&nums[r]==nums[r-1]) 
                    r--;
                l++;
                r--;
            }
            else if(sum<0) 
                l++;
            else 
                r--;
        }
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans=threeSum(nums);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j=0; j<3; j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}