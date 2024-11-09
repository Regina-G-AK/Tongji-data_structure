#include<iostream>
using namespace std;

const int T = 12;

int main()
{
    double x, sum = 0;
    for (int i = 0; i < T; i++)
    {
        scanf("%lf", &x);
        sum += x;
    }
    printf("¥%.2lf\n", sum / T);
    return 0;
}
