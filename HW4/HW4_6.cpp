#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to, weight;
};

void dijkstra(const vector<vector<Edge>>& adj, int start, vector<int>& dist) 
{
    const int INF = INT_MAX;
    dist.assign(adj.size(), INF); // 初始化所有点到起点的距离为无穷大
    dist[start] = 0; // 起点到自身的距离为0
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 最小堆
    pq.push({0, start}); // 将起点加入优先队列
    while (!pq.empty()) 
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) 
            continue; // 若当前距离不是最优，跳过
        for (const Edge& e : adj[u]) 
        {
            if (dist[e.to] > dist[u] + e.weight) 
            {
                dist[e.to] = dist[u] + e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }
}

int main() 
{
    int N, M;
    cin >> N >> M;
    vector<vector<Edge>> adj(N + 1);
    for (int i = 0; i < M; ++i) 
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }
    int H, R;
    cin >> H >> R;
    vector<bool> is_grass(N + 1, false);
    for (int i = 0; i < H; ++i) 
    {
        int a;
        cin >> a;
        is_grass[a] = true;
    }

    vector<int> grass_points;
    for (int i = 1; i <= N; ++i) 
    {
        if (is_grass[i]) 
        {
            grass_points.push_back(i);
        }
    }

    // 从每个草地点出发计算到所有点的最短路径
    vector<vector<int>> dist_grass_to_all(grass_points.size(), vector<int>(N + 1, 0));
    for (size_t i = 0; i < grass_points.size(); ++i) 
    {
        dijkstra(adj, grass_points[i], dist_grass_to_all[i]);
    }

    for (int q = 0; q < R; ++q) 
    {
        int start, end;
        cin >> start >> end;

        int min_dist = INT_MAX;

        // 如果起点和终点是同一个点
        if (start == end) 
        {
            if (is_grass[start]) 
            {
                cout << 0 << endl; // 如果是草地，距离为0
            } 
            else 
            {
                // 从起点到最近的草地再返回起点
                for (size_t i = 0; i < grass_points.size(); ++i) 
                {
                    min_dist = min(min_dist, dist_grass_to_all[i][start] * 2);
                }
                cout << (min_dist == INT_MAX ? -1 : min_dist) << endl;
            }
            continue;
        }

        // 遍历所有草地点，计算从 start -> 草地 -> end 的最短路径
        for (size_t i = 0; i < grass_points.size(); ++i) 
        {
            int path = dist_grass_to_all[i][start] + dist_grass_to_all[i][end];
            min_dist = min(min_dist, path);
        }

        cout << (min_dist == INT_MAX ? -1 : min_dist) << endl;
    }

    return 0;
}