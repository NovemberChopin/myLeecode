#include <iostream>
#include <structDefine.h>
using namespace std;

/**
 * 输入一个链表，反转链表后，输出新链表的表头。
 * input: {1, 2, 3}
 * output: {3, 2, 1}
 */
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode *pre = nullptr;
        ListNode *cur = pHead;
        ListNode *nex = nullptr;
        while (cur) {
            nex = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nex;
        }
        return pre;
    }
};