#include <vector>
#include <limits.h>
#include <unordered_map>
using namespace std;

class Solution {
public:
    /**
     * JZ42 连续子数组的最大和
     * 输入一个长度为n的整型数组array，数组中的一个或连续多个整数组成一个子数组，
     * 子数组最小长度为1。求所有子数组的和的最大值。
     */
    int FindGreatestSumOfSubArray(vector<int> array) {
        int len = array.size();
        // 以array[i]结尾的最大字数组之和为 dp[i]
        vector<int> dp(len);
        // base case
        dp[0] = array[0];
        for (int i=1; i< len; i++) {
            dp[i] = max(dp[i-1] + array[i], array[i]);
        }
        int res = INT_MIN;
        for (int i = 0; i<len; i++)
            res = max(res, dp[i]);
        return res;
    }

    // 动态规划，空间优化
    int FindGreatestSumOfSubArray(vector<int> array) {
        
        int len = array.size();
        // base case
        int dp_pre = array[0];
        int dp_cur = 0, res = dp_pre;
        
        for (int i=1; i< len; i++) {
            dp_cur = max(dp_pre + array[i], array[i]);
            dp_pre = dp_cur;
            res = max(res, dp_cur);
        }
        return res;
    }

    /**
     * JZ48 最长不含重复字符的子字符串
     * 
     */
    int lengthOfLongestSubstring(string s) {
        // 以s[i]字符结尾的不重复字符串长度为 dp[i]
        vector<int> dp(s.size());
        unordered_map<char, int> mp;
        dp[0]=1;
        mp[s[0]]=0;    // 存储字符的位置
        int ans=1;
        for(int i=1;i<s.size();i++){
            if(mp.count(s[i])){
                // 之前存在字符 s[i]
                // 不在最大串中   在最大串中
                dp[i]=min(dp[i-1]+1,i-mp[s[i]]);
                mp[s[i]]=i;
            }else{
                // 之前不存在
                mp[s[i]]=i;
                dp[i]=dp[i-1]+1;
            }
            ans=max(ans,dp[i]);
        }
        return ans;
    }

    /**
     * JZ63 买卖股票的最好时机(一)
     */
    int maxProfit(vector<int>& prices) {
        // dp[i] 表示第i天最大利润为（最大差值）
        vector<int> dp(prices.size());
        // base case
        dp[0] = 0;
        int minPri = prices[0];
        for (int i = 1; i<prices.size(); i++) {
            dp[i] = max(dp[i-1], prices[i]-minPri);
            // 寻找最低价格
            minPri = min(prices[i], minPri);
        }
        int res = INT_MIN;
        for (int i=0; i<prices.size(); i++)
            res = max(res, dp[i]);
        return res;
    }
    // 压缩数组
    int maxProfit(vector<int>& prices) {
        int minPrice = prices[0];
        int maxPro = INT_MIN;
        for (int i = 0; i<prices.size(); i++) {
            maxPro = max(maxPro, prices[i]-minPrice);
            // 寻找最低价格
            minPrice = min(prices[i], minPrice);
        }
        return maxPro;
    }


    /**
     * JZ47 礼物的最大价值
     */
    int maxValue(vector<vector<int> >& grid) {
        // dp[i][j] 表示在i j 点可以获得的最大礼物
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        // base case
        for (int i=1; i<=m; i++) {
            for (int j=1; j<=n; j++) {
                dp[i][j] = grid[i-1][j-1] + max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m][n];
    }
};