#include <iostream>
using namespace std;


struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

/**
 * 删除有序链表中相同的值
 */
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead) {
        ListNode* head = new ListNode(-1);
        head->next = pHead;
        ListNode *pre = head, *cur = pHead;
        
        while(cur) {
            if (cur->next && cur->val == cur->next->val) {
                cur = cur->next;
                while (cur->next && cur->val == cur->next->val) {
                    cur = cur->next;
                }
                cur = cur->next;
                pre->next = cur;
            } else {
                pre = cur;
                cur = cur->next;
            }
        }
        return head->next;
    }
};