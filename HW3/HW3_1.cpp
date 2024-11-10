#include <iostream>
using namespace std;

const int N = 200;

struct TreeNode
{
    char value;
    int flag = 0; 
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) : value(val), flag(0), left(nullptr), right(nullptr) {}
};

// 后序遍历函数
void postOrder(TreeNode* root)
{
    if (root == nullptr)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->value;
}

int main()
{
    int n;
    cin >> n;

    string operation;
    TreeNode* stack[N]; // 栈数组
    int top = -1;       // 栈顶指针
    TreeNode* root = nullptr; // 根节点
    string last_op;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> operation;
		
        if (operation == "push") // "push"操作
        {
            char nodeValue;
            cin >> nodeValue;
            TreeNode* newNode = new TreeNode(nodeValue);

            if (top == -1)
            {
                // 根节点
                root = newNode;
            }
            else if (stack[top]->flag == 0)
            {
                // 将新节点作为当前栈顶节点的左子节点
                stack[top]->left = newNode;
                stack[top]->flag = 1; // 更新flag表示左子节点已设置
            }
            else if (stack[top]->flag == 1)
            {
                // 将新节点作为当前栈顶节点的右子节点
                stack[top]->right = newNode;
                stack[top]->flag = 2; // 更新flag表示该节点的子节点已满
            }
            // 新节点入栈
            stack[++top] = newNode;
        }
        else if (operation == "pop") // "pop"操作
        {
            // 根据flag状态处理不同的情况
            if (stack[top]->flag == 0 || stack[top]->flag == 1)
            {
            	stack[top]->flag++;
                if(last_op=="pop")
                {
                	top--;
                	while(stack[top]->flag == 2)
                	{
                		top--;
                	}
                }
                    
            }
            else if (stack[top]->flag == 2)
            {
                while (stack[top]->flag == 2)
                    // 如果flag == 2，弹出当前节点
                    top--;
            }
        }
        last_op = operation;
    }

    postOrder(root);
    return 0;
}
