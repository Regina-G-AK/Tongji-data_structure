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
private:
    static bool cmp(int a, int b) 
    {
        string sa = to_string(a);
        string sb = to_string(b);
        return sa + sb > sb + sa;
    }
public:
    std::string largestNumber(std::vector<int>& nums) {
        // 这里填写你的代码 
        sort(nums.begin(), nums.end(), Solution::cmp);
        if (nums[0] == 0) {
            return "0";
        }
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