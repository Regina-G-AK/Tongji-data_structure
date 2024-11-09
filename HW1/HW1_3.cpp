#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

typedef struct Node 
{
    int n;
    int a;
    struct Node* next;
} Node;

Node* createLinkedList(int n, int a) 
{
    Node* head = NULL;
    Node* current = NULL;
    for (int i = 1; i <= n; ++i) 
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) 
            exit(1); // 内存分配失败则退出程序

        newNode->n = i;
        newNode->a = a;
        newNode->next = NULL;
        
        if (current == NULL) 
            head = newNode;
        else 
            current->next = newNode;
        current = newNode;
    }
    return head;
}

string turn_to_string(int x)
{
	string s;
	while (x%10||x/10)
	{
		s+=(x%10+'0');
		x/=10;
	}
	reverse(s.begin(),s.end());
	return s;
}

string multiply(string a, string b) 
{
    string result;
	string v(a.size()+b.size(), 0);
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	for (int i = 0; i < a.length(); i++)
	{
		for (int j = 0; j < b.length(); j++)
		{
			v[i + j] += (a[i] - '0') * (b[j] - '0');
			if (v[i + j] >= 10)
			{
				v[i + j + 1] += v[i + j] / 10;
				v[i + j] %= 10;
			}
		}
	}
	int len = a.length() + b.length();
	while (len > 1 && v[len - 1] == 0)
		len--;
	result.resize(len);
	for (int i = 0; i < len; i++)
		result[i] = char(v[i] + '0');
	reverse(result.begin(), result.end());
	return result;
}

string add(string a, string b)
{
	string s;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if (a.length() != b.length())
	{
		while (a.length() < b.length())
			a += '0';
		while (a.length() > b.length())
			b += '0';
	}
	int len = a.length();
	int add = 0;
	for (int i = 0; i < len; i++)
	{
		s += char((a[i] + b[i] - '0' - '0' + add) % 10 + '0');
		add = (a[i] - '0' + b[i] - '0' + add) / 10;
	}
	if (add != 0)
		s += char(add + '0');
	reverse(s.begin(), s.end());
	return s;
}

string calculateSeriesSum(Node* head)
{
    string result="0",s="1";
    Node* current = head;
    while (current != NULL) 
    {
    	s=multiply(s,turn_to_string(current->a));
        result =add(result,multiply(turn_to_string(current->n),s));
        current = current->next;
    }
    return result;
}

int main() 
{
    int n, a;
    cin>>n>>a;

    Node* head = createLinkedList(n, a);
    cout<< calculateSeriesSum(head)<<endl;
    
    while (head != NULL) 
    {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}