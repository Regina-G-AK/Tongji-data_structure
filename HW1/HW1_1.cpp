#include<iostream>
using namespace std;

const int N=1e5+5;

int main()
{
  int n,m;
  int a[N]={0};
  cin>>n>>m;
  for(int i=1;i<=n;i++)
   	cin>>a[i];
  while(m>=n)
    m-=n;
	for(int i=n-m+1;i<=n;i++)
		cout<<a[i]<<" ";
	for(int i=1;i<=n-m;i++)
		cout<<a[i]<<" ";
  return 0;
}
