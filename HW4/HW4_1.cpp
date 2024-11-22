#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> adj_list;
vector<int> vis;

// DFS 遍历连通分量
void dfs(int node, vector<int> &component)
{
    vis[node] = 1;
    component.push_back(node);
    for (int neighbor : adj_list[node])
    {
        if (!vis[neighbor])
        {
            dfs(neighbor, component);
        }
    }
}

// BFS 遍历连通分量
void bfs(int start, vector<int> &component)
{
    queue<int> q;
    q.push(start);
    vis[start] = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        component.push_back(node);

        for (int neighbor : adj_list[node])
        {
            if (!vis[neighbor])
            {
                vis[neighbor] = 1;
                q.push(neighbor);
            }
        }
    }
}

void print_components(const vector<vector<int>> &components)
{
    for (const auto &component : components)
    {
        cout << "{";
        for (size_t i = 0; i < component.size(); ++i)
        {
            if (i > 0)
                cout << " ";
            cout << component[i];
        }
        cout << "}";
    }
    cout << endl;
}

int main()
{
    int n, m;
    cin >> n >> m;

    adj_list.resize(n);
    vis.resize(n, 0);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
        // 无向图
    }

    for (int i = 0; i < n; ++i)
    {
        sort(adj_list[i].begin(), adj_list[i].end());
    }

    // DFS 找连通分量
    vector<vector<int>> dfs_components;
    fill(vis.begin(), vis.end(), false);
    for (int i = 0; i < n; ++i)
    {
        if (!vis[i])
        {
            vector<int> component;
            dfs(i, component);
            dfs_components.push_back(component);
        }
    }

    // BFS 找连通分量
    vector<vector<int>> bfs_components;
    fill(vis.begin(), vis.end(), false);
    for (int i = 0; i < n; ++i)
    {
        if (!vis[i])
        {
            vector<int> component;
            bfs(i, component);
            bfs_components.push_back(component);
        }
    }

    // 输出结果
    print_components(dfs_components);
    print_components(bfs_components);

    return 0;
}
