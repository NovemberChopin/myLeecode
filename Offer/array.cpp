#include <iostream>
#include <vector>
using namespace std;

/**
 * JZ1 二维数组中的查找
 * 
 * 从左下角元素往上查找，右边元素是比这个元素大，上边是的元素比这个元素小。
 * 于是，target比这个元素小就往上找，比这个元素大就往右找。如果出了边界，
 * 则说明二维数组中不存在target元素。
 */
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.size() ==0 || array[0].size() ==0) 
            return false;
        int rows = array.size();
        int cols = array[0].size();
        int i = rows-1, j=0;    // 左下角元素下标
        while (i>=0 && j<cols) {
            if (target < array[i][j])
                i--;
            else if (target > array[i][j])
                j++;    // 查找元素较大，往上找
            else 
                return true;
        }
        return false;
    }

    /* 二分法 */
    bool Find(int target, vector<vector<int> > array) {
        if (array.size() ==0 || array[0].size() ==0)
            return false;
        for (int i=0; i<array.size(); i++) {
            int low = 0;
            int high = array[i].size()-1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (target > array[i][mid])
                    low = mid + 1;
                else if (target < array[i][mid])
                    high = mid - 1;
                else
                    return true;
            }
        }
        return false;
    }
};

/**
 * JZ7 斐波那契数列
 * 现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0，第1项是1） (n≤39)
 */ 
class Solution {
public:
    /* 递归 时间：O(n^2)*/
    int Fibonacci(int n) {
        if (n==0 || n==1)
            return n;
        return Fibonacci(n-1) + Fibonacci(n-2);
    }
    
    /* 备忘录版： 时间：O(n) */
    int Fibonacci(int n) {
        vector<int> dp(n+1, 0);
        return helper(n, dp);
    }
    int helper(int n, vector<int>& dp) {
        if (n==0 || n==1) return n;
        if (dp[n] != 0) return dp[n];
        return dp[n] = helper(n-1, dp) + helper(n-2, dp);
    }
    
    /* 动态规划 时间：O(n) */
    int Fibonacci(int n) {
        if (n==0 || n==1) return n;
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for (int i=2; i<=n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
    
    /* 继续优化空间 */
    int Fibonacci(int n) {
        if (n==0 || n==1) return n;
        int pre = 0, cur = 1, sum=0;
        for (int i=2; i<=n; i++) {
            sum = pre + cur;
            pre = cur;
            cur = sum;
        }
        return sum;
    }
};