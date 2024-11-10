#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int left, right;
};

int time_to_infect_tree(int n, int start, vector<Node>& nodes) {
    // 建立邻接表
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        if (nodes[i].left != -1) {
            adj[i].push_back(nodes[i].left);
            adj[nodes[i].left].push_back(i);
        }
        if (nodes[i].right != -1) {
            adj[i].push_back(nodes[i].right);
            adj[nodes[i].right].push_back(i);
        }
    }
    
    // BFS传播感染
    vector<int> infected_time(n, -1); // 记录每个节点的感染时间，-1表示未感染
    queue<int> q;
    q.push(start);
    infected_time[start] = 0;
    
    int max_time = 0;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        int current_time = infected_time[node];
        
        for (int neighbor : adj[node]) {
            if (infected_time[neighbor] == -1) { // 未感染
                infected_time[neighbor] = current_time + 1;
                max_time = max(max_time, infected_time[neighbor]);
                q.push(neighbor);
            }
        }
    }
    
    return max_time;
}

int main() {
    int n, start;
    cin >> n >> start;
    
    vector<Node> nodes(n);
    for (int i = 0; i < n; ++i) {
        cin >> nodes[i].left >> nodes[i].right;
    }
    
    cout << time_to_infect_tree(n, start, nodes) << endl;
    return 0;
}
