#include<iostream>
#include<string>
using namespace std;

const int N = 260;

int main()
{
	while (1)
	{
		char s[N]={0};
		int score = 0;
		cin.getline(s,N);
		if (s[0] == '#')
			return 0;
		for (int i = 0; s[i]!=0; i++)
		{
			if (s[i] == ' ')
				;
			else if(s[i]>='A'&&s[i]<='Z')
				score += (s[i] - 'A' + 1) * (i + 1);
			else
				;
		}
		printf("%d\n", score);
	}
	return 0;
}