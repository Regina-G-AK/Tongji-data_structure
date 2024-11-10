#include <iostream>
#include <stdio.h>
#include <stack>
#include <string.h>
#include <map>

using namespace std;
const int maxn=105;
stack<int> val;  //存储操作数和中间运算结果
stack<char> op;  //存储运算符
map<char,int> maps;  //存储相应运算符的优先级，数值大代表优先级高

//求!a
void opNot(int a)
{
    while(!op.empty() && op.top()=='!') 
    {
        op.pop();
        a=!a;
    }
    val.push(a);
}
int main() 
{
    char ch;
    int a,b,t=0;
    maps['!']=3;maps['&']=2;maps['|']=1;
    while((ch=getchar())!=EOF) {
        t++;
        while(!val.empty())
            val.pop();
        while(!op.empty())
            op.pop();
        do {
            if(ch==' ')
                continue;
            /*
            遇到V\F，查看之前的表达式中(即栈op中)是否存在优先级高的单目运算符!。
            若存在，将这些单目运算符出op栈，对操作数进行相应的运算，再将运算结果压入val栈
            */
            if(ch=='V') 
            {
                a=1;
                opNot(a);
            } 
            else if(ch=='F') 
            {
                a=0;
                opNot(a);
            }
            //若遇到(,直接入op栈
            else if(ch=='(') 
            {
                op.push('(');
            }
            /*
            当遇到'('，将op中的运算符出栈，并将val栈中退出两个操作数，求值后将结果如val栈
            直至遇到'('结束。这里不需要考虑运算符为!的情况，因为之前肯定已经处理过了。

            这里还要注意的是，很有可能在'('前有!运算符，所以再求出(...)内的值后，不能就以为ok了。
            还要判断op栈顶上是否存在'!'，若存在，还要对结果取!。
            */
            else if(ch==')') 
            {
                while(op.top()!='(') 
                {
                    a=val.top();
                    val.pop();
                    b=val.top();
                    val.pop();
                    if(op.top()=='|')
                        val.push(a|b);
                    else
                        val.push(a&b);

                    op.pop();
                }
                op.pop(); //将'('出栈
                //若(...)前有！，则将括号算出来的结果取！
                while(!op.empty() && op.top()=='!')
                {
                    op.pop();
                    a=val.top();
                    val.pop();
                    val.push(!a);
                }
            } 
            else 
            {
                /*
                若ch为'!'，则不执行while循环，直接入op栈。
                若ch是其它双目运算符，则计算op栈顶中优先级比ch高的双目运算符。
                每弹出其中一个，从val栈顶退出两个操作数a,b，求结果后入val栈。
                进行完所有op栈顶中优先级比ch高的双目运算符后，再将ch压入op栈
                */
                while(!op.empty() && op.top()!='(' && op.top()!='!' && maps[op.top()]>=maps[ch]) {
                    a=val.top();
                    val.pop();
                    b=val.top();
                    val.pop();
                    if(op.top()=='|')
                        val.push(a|b);
                    else
                        val.push(a&b);
                    op.pop();
                }
                op.push(ch);  //一开始都忘记把ch入栈了。。。
            }
        } while((ch=getchar())!='\n' && ch!=EOF);
        /*扫描完所有表达式后，若op栈中还有运算符，则继续计算。*/
        while(!op.empty()) {
            ch=op.top();
            op.pop();
            a=val.top();
            val.pop();
            b=val.top();
            val.pop();
            if(ch=='|')
                val.push(a|b);
            else
                val.push(a&b);
        }
        if(val.top()==1)
            ch='V';
        else
            ch='F';
        printf("Expression %d: %c\n",t,ch);
    }

    return 0;
}