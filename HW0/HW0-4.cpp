#include<stdio.h>

int josephus(int n, int m) 
{
    int survivor = 0;  // 初始化f(1, m) = 0
    for (int i = 2; i <= n; i++) 
        survivor = (survivor + m) % i;
    return survivor;
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	printf("%d\n",josephus(n,m));	
	return 0;
}