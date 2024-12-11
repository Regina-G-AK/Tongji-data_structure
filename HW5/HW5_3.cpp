/**
 * @file    template.cpp
 * @name    p138模板程序
 * @date    2022-11-20
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
class Solution {
public:
    int solve(vector<vector<string>> &old_chart, vector<vector<string>> &new_chart) {
        // 这里填写你的代码
        vector<string> old_list,new_list;
        for(vector<string> a:old_chart)
        {
            for(string s:a)
            {
                old_list.push_back(s);
            }
        }
        for(vector<string> a:new_chart)
        {
            for(string s:a)
            {
                new_list.push_back(s);
            }
        } // 一维化
        // 建立位置的映射关系
        map<string,int> old_pos;
        for(int i=0;i<old_list.size();i++)
            old_pos[old_list[i]]=i;
        // 构建排列perm[i]= pos of new_list[i] in old_list
        // 建立一个排列，表示每个位置要换到哪里
        vector<int> perm(old_list.size());
        for(int i=0;i<new_list.size();i++)
            perm[i]=old_pos[new_list[i]];

        vector<bool> vis(old_list.size(),false);
        int cnt=0; // 循环数量
        for(int i=0;i<perm.size();i++)
        {
            if(!vis[i])
            {
                cnt++;
                int j=i;
                while(!vis[j])
                {
                    vis[j]=true;
                    j=perm[j];
                }
            }
        }
        int min_swaps=perm.size()-cnt; // 最少交换次数等于元素总数减去循环数
        return min_swaps;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
    std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));

    for( int i = 0; i < n; i ++ ) {
        for( int j = 0; j < m; j ++ ) {
            std::cin >> old_chart[i][j];
        }
    }
    for( int i = 0; i < n; i ++ ) {
        for( int j = 0; j < m; j ++ ) {
            std::cin >> new_chart[i][j];
        }
    }

    Solution s;
    std::cout << s.solve(old_chart, new_chart) << std::endl;
    return true;
}
