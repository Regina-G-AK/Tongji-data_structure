#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int to, weight;
};

void dijkstra(const vector<vector<Edge>>& adj, int start, vector<int>& dist) 
{
    const int INF = INT_MAX;
    dist.assign(adj.size(), INF);// 初始化所有点到起点的距离为无穷大
    dist[start] = 0;// 起点到自身的距离为0
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;// 最小堆存储当前点的最短路
    pq.push({0, start});// 将起点加入优先队列
    while (!pq.empty()) 
    {
        int d = pq.top().first;// 当前点的最短距离
        int u = pq.top().second;// 当前点编号
        pq.pop();
        if (d > dist[u]) 
            continue;// 若当前距离不是最优，跳过
        for (const Edge& e : adj[u]) //遍历邻接点
        {
            if (dist[e.to] > dist[u] + e.weight) //若有更短路径
            {
                dist[e.to] = dist[u] + e.weight;// 更新目标点的距离
                pq.push({dist[e.to], e.to});// 将目标点加入队列
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
    vector<vector<int>> dist_start_to_grass(R + 1, vector<int>(N + 1, 0));
    vector<int> dist_all_to_grass(N + 1, 0);
    vector<int> grass_points;
    for (int i = 1; i <= N; ++i) 
    {
        if (is_grass[i]) 
        {
            grass_points.push_back(i);
        }
    }
    
    vector<int> temp_dist(N + 1, INT_MAX);// 暂存从草地到其它点的距离
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int grass : grass_points) 
    {
        temp_dist[grass] = 0;
        pq.push({0, grass});
    }
    while (!pq.empty()) 
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > temp_dist[u]) 
            continue;
        for (const Edge& e : adj[u]) 
        {
            if (temp_dist[e.to] > temp_dist[u] + e.weight) 
            {
                temp_dist[e.to] = temp_dist[u] + e.weight;// 更新最短距离
                pq.push({temp_dist[e.to], e.to});
            }
        }
    }
    dist_all_to_grass = temp_dist;//保存从所有草地到其它点的距离
    
    vector<vector<int>> dist_grass_to_all(grass_points.size(), vector<int>(N + 1, 0));
    for (size_t i = 0; i < grass_points.size(); ++i) 
    {
        dijkstra(adj, grass_points[i], dist_grass_to_all[i]);
    }

    for (int q = 0; q < R; ++q) 
    {
        int start, end;
        cin >> start >> end;
        if (start == end) 
        {
            if (is_grass[start]) 
            {
                cout << 0 << endl;
            } 
            else 
            {
                int min_dist = INT_MAX;
                for (int grass : grass_points) 
                {
                    int path = dist_all_to_grass[start] + dist_grass_to_all[0][start];
                    min_dist = min(min_dist, path);
                }
                cout << min_dist << endl;
            }
        } 
        else 
        {
            int min_dist = INT_MAX;
            for (int grass : grass_points) 
            {
                int path = dist_all_to_grass[start] + dist_grass_to_all[0][end];
                min_dist = min(min_dist, path);
            }
            cout << min_dist << endl;
        }
    }
    return 0;
}