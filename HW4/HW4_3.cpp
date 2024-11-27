#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int u, v, weight;
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

int find_parent(vector<int> &parent, int x)
{
    if (parent[x] != x)
    {
        parent[x] = find_parent(parent, parent[x]); // 路径压缩
    }
    return parent[x];
}

void union_sets(vector<int> &parent, vector<int> &rank, int x, int y)
{
    int root_x = find_parent(parent, x);
    int root_y = find_parent(parent, y);
    if (root_x != root_y)
    {
        if (rank[root_x] > rank[root_y])
        {
            parent[root_y] = root_x;
        }
        else if (rank[root_x] < rank[root_y])
        {
            parent[root_x] = root_y;
        }
        else
        {
            parent[root_y] = root_x;
            rank[root_x]++;
        }
    }
}

int main()
{
    int n;
    cin >> n;

    vector<Edge> edges;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int dist;
            cin >> dist;
            if (i < j) // 避免重复存储
            {
                edges.push_back({i, j, dist});
            }
        }
    }

    int m;
    cin >> m;

    vector<int> parent(n + 1), rank(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i; // 初始化并查集
    }

    // 处理已连通的村庄
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        union_sets(parent, rank, a, b);
    }

    // Kruskal 算法求最小生成树
    sort(edges.begin(), edges.end());
    int total_cost = 0;
    for (const auto &edge : edges)
    {
        if (find_parent(parent, edge.u) != find_parent(parent, edge.v))
        {
            union_sets(parent, rank, edge.u, edge.v);
            total_cost += edge.weight;
        }
    }

    cout << total_cost << endl;
    return 0;
}
