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
};