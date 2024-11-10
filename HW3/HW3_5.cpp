#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1001;  // 最大节点数
const int MAXLOG = 11;   // log2(1000) ≈ 10，所以最多需要11层

int N, M;
vector<int> tree[MAXN];  // 邻接表表示树
int parent[MAXN];        // 父节点
int depth[MAXN];         // 节点的深度
int ancestor[MAXN][MAXLOG];  // ancestor[i][j]表示节点i的2^j层祖先

// 深度优先搜索初始化父节点和深度
void dfs(int node, int dep) {
    depth[node] = dep;
    for (int child : tree[node]) {
        if (depth[child] == -1) {  // 未访问过
            parent[child] = node;
            dfs(child, dep + 1);
        }
    }
}

// 预处理倍增表
void preprocess() {
    // 初始化父节点和祖先表
    for (int i = 1; i <= N; i++) {
        ancestor[i][0] = parent[i];  // 2^0 = 1层祖先是直接父节点
    }

    for (int j = 1; j < MAXLOG; j++) {
        for (int i = 1; i <= N; i++) {
            if (ancestor[i][j-1] != -1) {
                ancestor[i][j] = ancestor[ancestor[i][j-1]][j-1];
            }
        }
    }
}

// 查找节点u和v的LCA
int findLCA(int u, int v) {
    // 使u和v的深度相同
    if (depth[u] < depth[v]) swap(u, v);

    // 让u和v的深度相同
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = ancestor[u][i];
        }
    }

    // 如果u和v已经相同，则返回其中一个
    if (u == v) return u;

    // 向上跳直到找到公共祖先
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (ancestor[u][i] != ancestor[v][i]) {
            u = ancestor[u][i];
            v = ancestor[v][i];
        }
    }

    // 返回其父节点（即LCA）
    return parent[u];
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        cin >> N >> M;
        
        // 清空树的结构和其他相关数组
        for (int i = 1; i <= N; ++i) {
            tree[i].clear();
            parent[i] = -1;  // 重置父节点
            depth[i] = -1;   // 重置深度
            for (int j = 0; j < MAXLOG; ++j) {
                ancestor[i][j] = -1;  // 重置倍增表
            }
        }

        // 读取树的边
        int a, b;
        vector<int> in_degree(N + 1, 0);  // 用来确定根节点

        for (int i = 1; i < N; ++i) {
            cin >> a >> b;
            tree[a].push_back(b);
            in_degree[b]++;  
        }

        // 确保根节点的选择正确
        int root = 1;  // 默认选择节点1为根节点
        for (int i = 1; i <= N; ++i) {
            if (in_degree[i] == 0) {  // 入度为1的节点可能是根节点
                root = i;
                break;
            }
        }

        // 初始化根节点的父节点和深度
        parent[root] = -1;  // 根节点没有父节点
        fill(depth, depth + MAXN, -1);  // 设置为未访问
        dfs(root, 0);  // 从根节点开始DFS
        preprocess();  // 进行倍增表预处理

        // 处理查询
        for (int i = 1; i <= M; i++) {
            int x, y;
            cin >> x >> y;
            cout << findLCA(x, y) << endl;
        }
    }
    
    return 0;
}
