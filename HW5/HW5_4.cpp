/**
 * @name    template.cpp
 * @brief   p142模板程序
 * @date    2022-12-02
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class FreqStack{
    private:
    map<int, int> freq_map;                 // 记录每个元素的频率
    map<int, vector<int>> group_map;        // 记录每个频率对应的元素栈
    int max_freq;                           // 当前最大频率

public:
    FreqStack() : max_freq(0) {}

    void push(int x)
    {
        // 更新频率
        freq_map[x]++;
        int f = freq_map[x];

        // 更新最大频率
        if (f > max_freq)
        {
            max_freq = f;
        }

        // 将元素加入对应频率的栈
        group_map[f].push_back(x);
    }

    int pop()
    {
        // 从最大频率栈中取出元素
        int x = group_map[max_freq].back();
        group_map[max_freq].pop_back();

        // 如果最大频率栈为空，降低最大频率
        if (group_map[max_freq].empty())
        {
            group_map.erase(max_freq); // 清理空的频率组
            max_freq--;
        }

        // 更新频率映射
        freq_map[x]--;
        if (freq_map[x] == 0)
        {
            freq_map.erase(x); // 如果频率为 0，移除该元素
        }

        return x;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    FreqStack fs;
    while (n --) {
        std::string order;
        std::cin >> order;
        if (order == "push") {
            int val;
            std::cin >> val;
            fs.push(val);
        }
        else if (order == "pop") {
            std::cout << fs.pop() << std::endl;
        }
    }
    return 0;
}
