/**
 * @file    template.cpp
 * @name    模板程序
 * @date    2022-11-22
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
    bool cmp(int a, int b) {
        // 这里填写你的代码 
        string sa = to_string(a);
        string sb = to_string(b);
        return sa + sb > sb + sa;
    }

    std::string largestNumber(std::vector<int>& nums) {
        // 这里填写你的代码 
        // sort(nums.begin(), nums.end(), cmp); 
        sort(nums.begin(), nums.end(), [this](int a, int b) {
            return cmp(a, b);
        });
        string res;
        for (int i = 0; i < nums.size(); i++) {
            res += to_string(nums[i]);
        }
        return res;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i ++ ) {
        std::cin >> nums[i];
    }
    Solution s;
    std::cout << s.largestNumber(nums) << std::endl;
    return 0;
}