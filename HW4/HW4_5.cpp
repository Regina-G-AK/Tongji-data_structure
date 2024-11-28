#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Course
{
    int time;                // 课程所需时间
    vector<int> next;        // 后续课程列表
    int earliest_finish = 0; // 最早完成时间
};

void solve()
{
    int n;
    cin >> n;

    vector<Course> courses(n + 1);
    vector<int> in_degree(n + 1, 0); // 入度数组

    // 输入课程信息
    for (int i = 1; i <= n; ++i)
    {
        int t, c;
        cin >> t >> c;
        courses[i].time = t;
        for (int j = 0; j < c; ++j)
        {
            int pre;
            cin >> pre;
            courses[pre].next.push_back(i); // 建立依赖关系
            in_degree[i]++;
        }
    }

    // 拓扑排序
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (in_degree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> topo_order; // 拓扑排序的结果
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        topo_order.push_back(curr);

        for (int next : courses[curr].next)
        {
            in_degree[next]--;
            if (in_degree[next] == 0)
            {
                q.push(next);
            }
        }
    }

    // 计算最早完成时间
    for (int i : topo_order)
    {
        for (int next : courses[i].next)
        {
            courses[next].earliest_finish = max(courses[next].earliest_finish, courses[i].earliest_finish + courses[i].time);
        }
    }

    // 找毕业时间（关键路径的终点）
    int min_graduation_time = 0;
    for (int i = 1; i <= n; ++i)
    {
        min_graduation_time = max(min_graduation_time, courses[i].earliest_finish + courses[i].time);
    }

    // 判断每门课程是否会影响毕业时间
    for (int i = 1; i <= n; ++i)
    {
        int original_graduation_time = min_graduation_time;

        // 将当前课程的学时增加 1，重新计算毕业时间
        int new_time = courses[i].time + 1;
        int new_graduation_time = 0;

        for (int j = 1; j <= n; ++j)
        {
            if (j == i)
            {
                new_graduation_time = max(new_graduation_time, courses[j].earliest_finish + new_time);
            }
            else
            {
                new_graduation_time = max(new_graduation_time, courses[j].earliest_finish + courses[j].time);
            }
        }

        // 输出结果：最早完成时间 + 是否会延长毕业时间
        cout << courses[i].earliest_finish + courses[i].time << " ";
        if (new_graduation_time > original_graduation_time)
            cout << "1";
        else
            cout << "0";
        cout << endl;
    }
}

int main()
{
    solve();
    return 0;
}