#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int bitset(int target,int n,vector<int> nums)
{
	int st=0,end=n;
	int mid=(st+end)/2;
	while(st<end)
	{
		mid=(st+end)/2;
		if(nums[mid]<=target)
		{
			st=mid+1;
		}
		else 
		{
			end=mid;
		}
	}
	return st;
}

int main()
{
	int n,m;
	cin>>n>>m;
	vector<int> nums,queries,ans;
	for(int i=1;i<=n;i++)
	{
		int a;
		cin>>a;
		nums.push_back(a);
	}
	for(int i=1;i<=m;i++)
	{
		int a;
		cin>>a;
		queries.push_back(a);
	}
	sort(nums.begin(),nums.end());
	for(int i=1;i<n;i++)
		nums[i]+=nums[i-1];
	for(int num: queries)
	{
		ans.push_back(bitset(num,n,nums));
	}
	for(int a:ans)
	{
		cout<<a<<" ";
	}
	
	return 0;
}