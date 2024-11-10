#include <iostream>
#include <string>
using namespace std;

struct Stack 
{
    int capacity;
    int top;
    int *elements;

    Stack(int cap) : capacity(cap), top(-1) 
    {
        elements = new int[cap];
    }

    ~Stack() 
    {
        delete[] elements;
    }

    bool isEmpty() 
    {
        return top == -1;
    }

    void push(int element) 
    {
        if (top < capacity - 1) 
        {
            elements[++top] = element;
        }
    }

    int pop() 
    {
        if (!isEmpty()) 
        {
            return elements[top--];
        }
        return -1; // 返回-1表示栈为空
    }
};

void longestValidParentheses(const string& s,int maxLen,int start) 
{
    int n = s.size();
    Stack st(n);
    int lastInvalid = -1;  // 记录最后一个非法右括号的位置

    for (int i = 0; i < n; ++i) 
    {
        if (s[i] == '(') 
        {
            st.push(i);
        } 
        else 
        {
            if (st.isEmpty()) 
            {
                lastInvalid = i;
            } 
            else 
            {
                st.pop();
                if (st.isEmpty()) 
                {
                    if (maxLen < i - lastInvalid) 
                    {
                        maxLen = i - lastInvalid;
                        start = lastInvalid + 1;
                    }
                } 
                else 
                {
                    if (maxLen < i - st.elements[st.top]) 
                    {
                        maxLen = i - st.elements[st.top];
                        start = st.elements[st.top] + 1;
                    }
                }
            }
        }
    }
}

int main() 
{
    string input;
    cin >> input;
    int maxLen = 0;
    int start = 0;
    longestValidParentheses(input,maxLen,start);
    cout << maxLen << " " << start << endl;
    return 0;
}
