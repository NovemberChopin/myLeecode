#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution
{
private:
    stack<int> stack1;
    stack<int> stack2;
public:
    /**
     * JZ5 用两个栈实现队列
     * 用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
     * 思路：入队就是简单的入队。出队从 stack2 出，分两种情况（stack2是否为空，
     * 如果不为空把 stack1 数据转移到 stack2）
     */ 
    void push(int node) {
        stack1.push(node);
    }
    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int num = stack2.top();
        stack2.pop();
        return num;
    }
};

/**
 * JZ20 包含min函数的栈
 * 正常情况下，栈的push，pop操作都为O(1),但是返回最小值，
 * 需要遍历整个栈，时间复杂度为O(n)，所以这里需要空间换时间的思想。
 */ 
class Solution {
public:
    // 空间换时间
    stack<int> sta, sta2;
    void push(int value) {
        sta.push(value);
        if (sta2.empty())
            sta2.push(value);
        else {
            int min = sta2.top();
            if (value >= min) 
                sta2.push(min);
            else sta2.push(value);
        }
    }
    void pop() {
        sta.pop();
        sta2.pop();
    }
    int top() {
        return sta.top();
    }
    int min() {
        return sta2.top();
    }
};

/**
 * JZ21 栈的压入、弹出序列
 * 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是
 * 否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列
 * 1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个
 * 弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
 * （注意：这两个序列的长度是相等的）
 * 输入：[1,2,3,4,5],[4,3,5,1,2]
 * 输出：false
 * 
 * 1. 初始化：用指针i指向pushV的第一个位置， 指针j指向popV的第一个位置
 * 2. 如果pushV[i] != popV[j]， 那么应该将pushV[i]放入栈中， ++i
 * 3. 否则，pushV[i]==popV[j], 说明这个元素是放入栈中立马弹出，
 *    所以，++i, ++j，然后应该检查popV[j]与栈顶元素是否相等，如果相等，++j, 并且弹出栈顶元素
 * 4. 重复2，3， 如果i==pushV.size(), 说明入栈序列访问完，此时检查栈是否为空，
 *    如果为空，说明匹配,否则不匹配
 */ 
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> st;
        int i = 0, j = 0;
        while (i < pushV.size()) {
            if (pushV[i] != popV[j]) {
                st.push(pushV[i]);
                i++;
            }
            else {
                i++; j++;
                while (!st.empty() && st.top() == popV[j]) {
                    st.pop();
                    j++;
                }
            }
        }
        return st.empty();
    }
};