#include<iostream>
#include<algorithm>
using namespace std;

const int N=2055;

struct Data
{
	int p;
	int e;
}a[N],b[N],ans[N*N];

bool cmp(Data i,Data j)
{
	return i.e<j.e;
}

void add(int m,int n)
{
	int i=1,j=1,k=0;
	while(i<=m&&j<=n)
	{
		if(a[i].e<b[j].e)
		{
			ans[k].p=a[i].p;
			ans[k].e=a[i].e;
			k++;
			i++;
		}
		else if(a[i].e>b[j].e)
		{
			ans[k].p=b[j].p;
			ans[k].e=b[j].e;
			k++;
			j++;
		}
		else
		{
			int tmp=a[i].p+b[j].p;
			if(tmp)
			{
				ans[k].p=tmp;
				ans[k].e=a[i].e;
				k++;
			}
			i++;
			j++;
		}
	}
	while(i<=m)
	{
		ans[k].p=a[i].p;
		ans[k].e=a[i].e;
		k++;
		i++;
	}
	while(j<=n)
	{
		ans[k].p=b[j].p;
		ans[k].e=b[j].e;
		k++;
		j++;
	}
	for(int q=0;q<k;q++)
	{
		cout<<ans[q].p<<" "<<ans[q].e<<" ";
	}
	cout<<endl;
}

void mul(int m,int n)
{
	int k=0;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			ans[k].p=a[i].p*b[j].p;
			ans[k].e=a[i].e+b[j].e;
			k++;
		}
	}
	sort(ans,ans+k,cmp);
	for(int i=0;i<k;i++)
	{
		for(int j=i+1;j<k;j++)
		{
			if(ans[i].e==ans[j].e)
			{
				ans[i].p+=ans[j].p;
				for(int l=j;l<k;l++)
				{
					ans[l].p=ans[l+1].p;
					ans[l].e=ans[l+1].e;
				}
				k--;
				j--;
			}
		}
	}
	for(int q=0;q<k;q++)
		if(ans[q].p)
			cout<<ans[q].p<<" "<<ans[q].e<<" ";
	cout<<endl;
}

int main()
{
	int n,m,k;
	cin>>m;
	for(int i=1;i<=m;i++)
		cin>>a[i].p>>a[i].e;
	sort(a+1,a+m+1,cmp);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>b[i].p>>b[i].e;
	sort(b+1,b+n+1,cmp);
	cin>>k;
	if(k==0)
		add(m,n);
	else if(k==1)
		mul(m,n);
	else
	{
		add(m,n);
		mul(m,n);
	}
	return 0;
}