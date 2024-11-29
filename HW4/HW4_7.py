def find_euler_paths(graph):
    n = len(graph)
    # 检查是否存在欧拉路径
    odd_degree = [i for i in range(n) if sum(graph[i]) % 2 == 1]
    if len(odd_degree) not in (0, 2):
        return []  # 如果奇数度顶点数量不为 0 或 2，则无欧拉路径

    start = odd_degree[0] if odd_degree else 0  # 如果有奇数度顶点，从其中一个开始；否则任选

    # 用于存储结果
    results = []

    def dfs(curr, path, edges_left):
        # 如果没有边剩下，记录路径
        if edges_left == 0:
            results.append(path[:])
            return

        for next_node in range(n):
            if graph[curr][next_node] > 0:  # 存在边
                # 标记边已访问
                graph[curr][next_node] -= 1
                graph[next_node][curr] -= 1
                # 递归继续搜索
                dfs(next_node, path + [next_node], edges_left - 1)
                # 回溯：恢复边
                graph[curr][next_node] += 1
                graph[next_node][curr] += 1

    # 统计图中边数
    total_edges = sum(sum(row) for row in graph) // 2
    dfs(start, [start], total_edges)
    return results


map = [
    [0, 1, 1, 0, 1],  # 顶点 1 与 2、3、5 相连
    [1, 0, 1, 0, 1],  # 顶点 2 与 1、3、5 相连
    [1, 1, 0, 1, 1],  # 顶点 3 与 1、2、4、5 相连
    [0, 0, 1, 0, 1],  # 顶点 4 与 3、5 相连
    [1, 1, 1, 1, 0]   # 顶点 5 与 1、2、3、4 相连
]

# 查找所有欧拉路径
euler_paths = find_euler_paths(map)
for path in euler_paths:
    print(" -> ".join(str(node + 1) for node in path))
