#include <stdio.h>

const int N=64;

int main() 
{
    int n;
    long long m[N] = {0}; // 雄蜂数量
    long long f[N] = {0}; // 雌蜂数量
    f[0] = 1;
    m[0] = 0;
    for (int i = 1; i < N; i++) 
    {
        f[i] = m[i-1]+1;
        m[i] = f[i-1] + m[i-1];
    }
    while (scanf("%d",&n)&&n!=-1) 
       printf("%ld %ld\n",m[n],m[n]+f[n]);    
    return 0;
}