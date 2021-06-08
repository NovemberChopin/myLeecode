#include <iostream>
#include <vector>

#include <structDefine.h>

using namespace std;


/**
 * 输入一个链表，按链表从尾到头的顺序返回一个ArrayList。
 * 输入：{67,0,24,58}
 * 返回：[58,24,0,67]
 */
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {

/* ----------------------- recursion ------------------------- */
        vector<int> arr;
        if (head == nullptr)
            return arr;
        arr = printListFromTailToHead(head->next);
        arr.push_back(head->val);
        return arr;
        
/* ------------- Non-recursion: reverse link ----------------- */
    //     vector<int> arr;
    //     ListNode* pre = nullptr;
    //     ListNode* cur = head;
    //     ListNode* nex = nullptr;
    //     while (cur) {
    //         nex = cur->next;
    //         cur->next = pre;
    //         pre = cur;
    //         cur = nex;
    //     }
    //     while (pre) {
    //         arr.push_back(pre->val);
    //         pre = pre->next;
    //     }
    //     return arr;
    }
};