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