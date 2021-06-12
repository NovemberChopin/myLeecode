#include <iostream>
#include <stack>
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