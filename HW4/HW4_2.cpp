#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

// BFS函数，计算从起点start出发六步以内的可达节点数
int bfs(int start, int n, vector<vector<int>>& adj_list) 
{
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    distance[start] = 0;
    int count = 1; // 起点本身
    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();
        for (int v : adj_list[u]) 
        {
            if (!visited[v]) 
            {
                visited[v] = true;
                distance[v] = distance[u] + 1;
                if (distance[v] <= 6) 
                {
                    q.push(v);
                    count++;
                }
            }
        }
    }
    return count;
}

int main() 
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) 
    {
        int a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    // 对每个节点计算六度空间内的可达节点数占总节点数的百分比
    for (int i = 0; i < n; i++) 
    {
        int reachable = bfs(i, n, adj_list);
        float percent = (float)reachable / n * 100;
        cout << fixed << setprecision(2) << percent << endl;
    }

    return 0;
}