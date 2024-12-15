#include <iostream>
#include <queue>
using namespace std;

struct Node 
{
    int val;
    int cnt;
    Node* lchild;
    Node* rchild;
};

void createNode(Node*& n,int value)
{
    n=new(nothrow) Node;
    if(!n)
        exit(-1);
    n->val=value;
    n->cnt=1;
    n->lchild=n->rchild=nullptr;
}

void Insert(Node*& T, int value)
{
	//根结点
	if (!T)
		createNode(T, value);
	else if (T->val == value) {
		T->cnt++;
	}
	else if (T->val > value) {
		if (T->lchild)
			Insert(T->lchild, value);
		else
			createNode(T->lchild, value);
	}
	else {
		if (T->rchild)
			Insert(T->rchild, value);
		else
			createNode(T->rchild, value);
	}
}

bool Delete(Node*& T, int value)
{
	if (!T)
		return false;  //没有该元素
	else if (T->val == value) {
		if (T->cnt != 1)
			T->cnt--;
		//只有单边子树
		else if (!T->rchild) {
			Node* q = T;
			T = T->lchild;
			delete q;
		}
		else if (!T->lchild) {
			Node* q = T;
			T = T->rchild;
			delete q;
		}
		//有左右两子树
		else {
			Node* q = T, * s = T->lchild;
			while (s->rchild) {
				q = s;
				s = s->rchild;
			}
			T->val = s->val;
			T->cnt = s->cnt;
			//特判如果一开始左孩子没有右子树 则q没有空出的右孩子来接s的左孩子
			//(s原先在哪里就有哪边孩子空出)
			if (q != T)
				q->rchild = s->lchild;
			else
				q->lchild = s->lchild;
			delete s;
		}
		return true;
	}
	else if (T->val > value)
		return Delete(T->lchild, value);
	else
		return Delete(T->rchild, value);
}

int Search(Node* T, int value)
{
	if (!T)
		return 0;
	else if (T->val == value)
		return T->cnt;
	else if (T->val > value) 
		return Search(T->lchild, value);
	else 
		return Search(T->rchild, value);
}

int GetMin(Node* T)
{
	if (T->lchild)
		return GetMin(T->lchild);
	else
		return T->val;
}

void Traverse(Node* T, queue<int>& q)
{
	if (!T)
		return;
	Traverse(T->lchild, q);
	q.push(T->val);
	Traverse(T->rchild, q);
}

int main() 
{
    int n;
    cin >> n;
    Node* root = nullptr;
    while (n--) 
    {
        int op;
        cin >> op;
        
        switch (op) 
        {
            case 1:
                int x;
                cin >> x;
                Insert(root, x);
                break;
            case 2:
                cin >> x;
                if (!Delete(root, x))
                    cout << "None" << endl;
                break;
            case 3:
                cin >> x;
                cout << Search(root, x) << endl;
                break;
            case 4:
                cout << GetMin(root) << endl;
                break;
            case 5:
                cin >> x;
                queue<int> q;
                Traverse(root,q);
                int ans=-1;
                while(!q.empty()&&q.front()<x)
                {
                    ans=q.front();
                    q.pop();
                }
                if (ans != -1)
                    cout << ans << endl;
                else
                    cout << "None" << endl;
                break;
        }
    }
    return 0;
}