#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

vector<int> topological_sort(int k, const vector<vector<int>>& conditions) // 拓扑排序
{
    vector<vector<int>> graph(k + 1);// 图
    vector<int> in_degree(k + 1, 0);// 入度
    for (const auto& cond : conditions) 
    {
        int a = cond[0], b = cond[1];
        graph[a].push_back(b);
        in_degree[b]++;
    }
    queue<int> q;
    for (int i = 1; i <= k; ++i) 
    {
        if (in_degree[i] == 0) // 入度=0，拓扑排序入队
        {
            q.push(i);
        }
    }
    vector<int> order;
    while (!q.empty()) 
    {
        if (q.size() > 1) 
        {
            return {};  // 矩阵不唯一，返回空
        }
        int current = q.front(); // 取队首
        q.pop();
        order.push_back(current); // 加入当前排序，相当于current元素已经排序成功
        for (int neighbor : graph[current]) // 遍历current元素所连接的元素，将其均入度-1
        {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) // 若出现入度=0，则入队
            {
                q.push(neighbor);
            }
        }
    }
    if (order.size() != k) // 若队列大小不满足k，则证明矩阵不成功
    {
        return {};  // 存在环的情况，返回空
    }
    return order;
}

void construct_matrix(int k, const vector<vector<int>>& row_conditions, const vector<vector<int>>& col_conditions) 
{
    vector<int> row_order = topological_sort(k, row_conditions);
    if (row_order.empty()) 
    {
        cout << -1 << endl;
        return;
    }
    vector<int> col_order = topological_sort(k, col_conditions);
    if (col_order.empty()) 
    {
        cout << -1 << endl;
        return;
    }
    unordered_map<int, int> row_pos, col_pos;
    for (int i = 0; i < k; ++i) 
    {
        row_pos[row_order[i]] = i;
        col_pos[col_order[i]] = i;
    }
    vector<vector<int>> matrix(k, vector<int>(k, 0));
    for (int num = 1; num <= k; ++num) 
    {
        int r = row_pos[num];
        int c = col_pos[num];
        matrix[r][c] = num;
    }
    for (const auto& row : matrix) 
    {
        for (int val : row) 
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() 
{
    int k, n, m;
    cin >> k >> n >> m;
    vector<vector<int>> row_conditions(n, vector<int>(2));
    for (int i = 0; i < n; ++i) 
    {
        cin >> row_conditions[i][0] >> row_conditions[i][1];
    }
    vector<vector<int>> col_conditions(m, vector<int>(2));
    for (int i = 0; i < m; ++i) 
    {
        cin >> col_conditions[i][0] >> col_conditions[i][1];
    }
    construct_matrix(k, row_conditions, col_conditions);
    return 0;
}