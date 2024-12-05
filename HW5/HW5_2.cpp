#include <iostream>
using namespace std;

struct Node 
{
    int val;
    int cnt;
    Node* left;
    Node* right;
};

struct BST 
{
    Node* root;
    BST() : root(nullptr) {}
};

void insert(BST& tree, int x) 
{
    if (tree.root == nullptr) 
    {
        tree.root = new Node();
        tree.root->val = x;
        tree.root->cnt = 1;
        tree.root->left = nullptr;
        tree.root->right = nullptr;
    } 
    else 
    {
        Node* current = tree.root;
        while (true) 
        {
            if (x < current->val) 
            {
                if (current->left == nullptr) 
                {
                    current->left = new Node();
                    current->left->val = x;
                    current->left->cnt = 1;
                    current->left->left = nullptr;
                    current->left->right = nullptr;
                    break;
                } 
                else 
                {
                    current = current->left;
                }
            } 
            else if (x > current->val) 
            {
                if (current->right == nullptr) 
                {
                    current->right = new Node();
                    current->right->val = x;
                    current->right->cnt = 1;
                    current->right->left = nullptr;
                    current->right->right = nullptr;
                    break;
                } 
                else 
                {
                    current = current->right;
                }
            } 
            else 
            {
                current->cnt++;
                break;
            }
        }
    }
}

int remove(BST& tree, int x) 
{
    Node* parent = nullptr;
    Node* current = tree.root;
    while (current != nullptr) 
    {
        if (x < current->val) 
        {
            parent = current;
            current = current->left;
        } 
        else if (x > current->val) 
        {
            parent = current;
            current = current->right;
        } 
        else 
        {
            if (current->cnt > 1)
            {
                current->cnt--;
                return 1;
            } 
            else 
            {
                if (current->left == nullptr && current->right == nullptr) 
                {
                    if (parent == nullptr) 
                    {
                        tree.root = nullptr;
                    } 
                    else if (parent->left == current) 
                    {
                        parent->left = nullptr;
                    } 
                    else 
                    {
                        parent->right = nullptr;
                    }
                    delete current;
                } 
                else if (current->left == nullptr) 
                {
                    if (parent == nullptr) 
                    {
                        tree.root = current->right;
                    } 
                    else if (parent->left == current) 
                    {
                        parent->left = current->right;
                    } 
                    else 
                    {
                        parent->right = current->right;
                    }
                    delete current;
                } 
                else if (current->right == nullptr) 
                {
                    if (parent == nullptr) 
                    {
                        tree.root = current->left;
                    } 
                    else if (parent->left == current) 
                    {
                        parent->left = current->left;
                    } 
                    else 
                    {
                        parent->right = current->left;
                    }
                    delete current;
                } 
                else 
                {
                    Node* predecessor = current->left;
                    Node* predecessorParent = current;
                    while (predecessor->right != nullptr) 
                    {
                        predecessorParent = predecessor;
                        predecessor = predecessor->right;
                    }
                    current->val = predecessor->val;
                    current->cnt = predecessor->cnt;
                    if (predecessorParent->left == predecessor) 
                    {
                        predecessorParent->left = predecessor->left;
                    } 
                    else 
                    {
                        predecessorParent->right = predecessor->left;
                    }
                    delete predecessor;
                }
                return 1;
            }
        }
    }
    return 0;
}

int count(BST& tree, int x) 
{
    Node* current = tree.root;
    while (current != nullptr) 
    {
        if (x < current->val) 
        {
            current = current->left;
        } 
        else if (x > current->val) 
        {
            current = current->right;
        } 
        else 
        {
            return current->cnt;
        }
    }
    return 0;
}

int findMin(BST& tree) 
{
    Node* current = tree.root;
    while (current->left != nullptr) 
    {
        current = current->left;
    }
    return current->val;
}

int findPredecessor(BST& tree, int x) 
{
    Node* current = tree.root;
    Node* predecessor = nullptr;
    while (current != nullptr) 
    {
        if (x <= current->val) 
        {
            current = current->left;
        } 
        else 
        {
            predecessor = current;
            current = current->right;
        }
    }
    if (predecessor != nullptr) 
    {
        Node* temp = predecessor->right;
        while (temp != nullptr) 
        {
            predecessor = temp;
            temp = temp->left;
        }
        return predecessor->val;
    } 
    else 
    {
        return -1; // 表示没有前驱
    }
}

int main() 
{
    int n;
    cin >> n;
    BST tree;
    while (n--) 
    {
        int op;
        cin >> op;
        switch (op) 
        {
            case 1:
                int x;
                cin >> x;
                insert(tree, x);
                break;
            case 2:
                cin >> x;
                if (!remove(tree, x))
                    cout << "None" << endl;
                break;
            case 3:
                cin >> x;
                cout << count(tree, x) << endl;
                break;
            case 4:
                cout << findMin(tree) << endl;
                break;
            case 5:
                cin >> x;
                int pred = findPredecessor(tree, x);
                if (pred != -1)
                    cout << pred << endl;
                else
                    cout << "None" << endl;
                break;
        }
    }
    return 0;
}