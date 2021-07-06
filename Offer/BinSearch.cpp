#include <iostream>
#include <stack>
#include <vector>
using namespace std;


/**
 * JZ6 旋转数组的最小数字
 * 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
 * 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
 * NOTE：给出的所有元素都大于0，若数组大小为0，请返回0
 * 
 * 输入：[3,4,5,1,2]
 * 输出：1
 */ 
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.size() == 0) return 0;
        int first = 0, last = rotateArray.size() - 1;
        while (first < last) {
            if (rotateArray[first] < rotateArray[last]) 
                return rotateArray[first];
            int mid = first + (last-first) / 2;
            // //如果左半数组为有序数组
            if (rotateArray[first] < rotateArray[mid])
                first = mid + 1;
            // //如果右半数组为有序数组
            else if (rotateArray[mid] < rotateArray[last])
                last = mid;
            else 
                first++;
        }
        return rotateArray[first];
    }
};