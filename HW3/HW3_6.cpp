#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

// 辅助函数：查找根节点在中序遍历中的位置
int findInOrderIndex(const string& inorder, char root) {
    for (int i = 0; i < inorder.size(); ++i) {
        if (inorder[i] == root) return i;
    }
    return -1;
}

// 递归构建树：根据前序遍历和中序遍历构建树
TreeNode* buildTree(const string& preorder, const string& inorder, int& preIndex, int inStart, int inEnd, unordered_map<char, int>& inorderMap, bool& isError) {
    if (inStart > inEnd) return nullptr;  // 递归边界，空树

    // 获取前序遍历中的根节点
    char rootVal = preorder[preIndex++];
    
    // 如果该节点不在中序遍历中，或者重复构建了树，返回错误
    if (inorderMap.find(rootVal) == inorderMap.end() || inorderMap[rootVal] < inStart || inorderMap[rootVal] > inEnd) {
        isError = true;
        return nullptr;
    }

    TreeNode* root = new TreeNode(rootVal);
    int rootIndex = inorderMap[rootVal];

    // 递归构建左右子树
    root->left = buildTree(preorder, inorder, preIndex, inStart, rootIndex - 1, inorderMap, isError);
    root->right = buildTree(preorder, inorder, preIndex, rootIndex + 1, inEnd, inorderMap, isError);

    return root;
}

// 后序遍历：递归输出后序遍历结果
void postOrder(TreeNode* root, string& result) {
    if (root == nullptr) return;
    postOrder(root->left, result);
    postOrder(root->right, result);
    result += root->val;
}

// 验证前序遍历和中序遍历是否可以构建唯一的二叉树
bool isValid(const string& preorder, const string& inorder) {
    if (preorder.size() != inorder.size()) return false;

    unordered_map<char, int> inorderMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }

    int preIndex = 0;
    bool isError = false; // 用于标记是否发生错误
    TreeNode* root = buildTree(preorder, inorder, preIndex, 0, inorder.size() - 1, inorderMap, isError);

    // 如果发生错误，或者没有构建完所有节点，返回false
    return !isError && preIndex == preorder.size();
}

int main() {
    string preorder, inorder;
    while (cin >> preorder >> inorder) {
        // 校验前序和中序是否有效
        if (!isValid(preorder, inorder)) {
            cout << "Error" << endl;
        } else {
            unordered_map<char, int> inorderMap;
            for (int i = 0; i < inorder.size(); ++i) {
                inorderMap[inorder[i]] = i;
            }

            int preIndex = 0;
            bool isError = false;
            TreeNode* root = buildTree(preorder, inorder, preIndex, 0, inorder.size() - 1, inorderMap, isError);

            string postorderResult;
            postOrder(root, postorderResult);
            cout << postorderResult << endl;
        }
    }
    return 0;
}
