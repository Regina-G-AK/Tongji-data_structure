#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct TreeNode {
    char data;
    int left, right;
};

vector<TreeNode> tree1, tree2;

// 递归计算树的深度
int compute_depth(const vector<TreeNode>& tree, int root) {
    if (root == -1) return 0; // 空节点深度为0
    int left_depth = compute_depth(tree, tree[root].left);
    int right_depth = compute_depth(tree, tree[root].right);
    return max(left_depth, right_depth) + 1;
}

// 检查两棵树是否同构
bool is_isomorphic(const vector<TreeNode>& tree1, int root1, const vector<TreeNode>& tree2, int root2) {
    if (root1 == -1 && root2 == -1) return true;  // 两个都是空树
    if (root1 == -1 || root2 == -1) return false; // 只有一个是空树，非同构
    if (tree1[root1].data != tree2[root2].data) return false; // 根节点值不同，非同构

    // 两种同构情况：不交换左右子树，或交换左右子树
    bool case1 = is_isomorphic(tree1, tree1[root1].left, tree2, tree2[root2].left) &&
                 is_isomorphic(tree1, tree1[root1].right, tree2, tree2[root2].right);
    bool case2 = is_isomorphic(tree1, tree1[root1].left, tree2, tree2[root2].right) &&
                 is_isomorphic(tree1, tree1[root1].right, tree2, tree2[root2].left);

    return case1 || case2;
}

// 查找根节点
int find_root(const vector<TreeNode>& tree) {
    unordered_set<int> child_nodes;
    for (const auto& node : tree) {
        if (node.left != -1) child_nodes.insert(node.left);
        if (node.right != -1) child_nodes.insert(node.right);
    }
    for (int i = 0; i < tree.size(); i++) {
        if (child_nodes.find(i) == child_nodes.end()) {
            return i; // i不在任何节点的孩子列表中，说明是根节点
        }
    }
    return -1; // 没有找到根节点
}

int main() {
    int N1, N2;
    cin >> N1;
    tree1.resize(N1);

    for (int i = 0; i < N1; i++) {
        char data;
        string left, right;
        cin >> data >> left >> right;
        tree1[i].data = data;
        tree1[i].left = (left == "-") ? -1 : stoi(left);
        tree1[i].right = (right == "-") ? -1 : stoi(right);
    }

    cin >> N2;
    tree2.resize(N2);

    for (int i = 0; i < N2; i++) {
        char data;
        string left, right;
        cin >> data >> left >> right;
        tree2[i].data = data;
        tree2[i].left = (left == "-") ? -1 : stoi(left);
        tree2[i].right = (right == "-") ? -1 : stoi(right);
    }

    // 如果节点数不同，直接判定为非同构
    if (N1 != N2) {
        cout << "No" << endl;
        cout << (N1 > 0 ? compute_depth(tree1, find_root(tree1)) : 0) << endl;
        cout << (N2 > 0 ? compute_depth(tree2, find_root(tree2)) : 0) << endl;
        return 0;
    }

    // 查找树的根节点
    int root1 = find_root(tree1);
    int root2 = find_root(tree2);

    // 计算树的深度
    int depth1 = compute_depth(tree1, root1);
    int depth2 = compute_depth(tree2, root2);

    // 判断是否同构并输出结果
    if (is_isomorphic(tree1, root1, tree2, root2)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    // 输出两棵树的深度
    cout << depth1 << endl;
    cout << depth2 << endl;

    return 0;
}
