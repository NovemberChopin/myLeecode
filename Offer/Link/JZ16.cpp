#include <iostream>
#include <structDefine.h>
using namespace std;

/**
 * 合并两个排序链表
 * input: {1,3,5},{2,4,6}
 * output: {1,2,3,4,5,6}
 *
 */
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        ListNode* listHead = new ListNode(-1);
        ListNode* p = listHead;
        
        while (pHead1 && pHead2) {
            if (pHead1->val <= pHead2->val) {
                p->next = pHead1;
                pHead1 = pHead1->next;
            } else {
                p->next = pHead2;
                pHead2 = pHead2->next;
            }
            p = p->next;
        }
        if (pHead1) 
            p->next = pHead1;
        else p->next = pHead2;
        
        return listHead->next;
    }
};