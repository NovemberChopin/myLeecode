#include <iostream>
using namespace std;


struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution {
public:
    ListNode* MeetingNode(ListNode* pHead) {
        // 一快一慢两指针，如果相遇，则存在环
        if (pHead == nullptr) return nullptr;
        ListNode* pSlow = pHead->next;
        if (pSlow == nullptr) return nullptr;
        ListNode* pFast = pSlow->next;
        while (pFast != nullptr && pSlow != nullptr) {
            if (pFast == pSlow) // 返回相遇节点
                return pFast;
            pSlow = pSlow->next;
            // 快指针走两步
            pFast = pFast->next;
            if (pFast != nullptr)
                pFast = pFast->next;
        }
        return nullptr;
    }
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        /* ---------一. 计算环的长度 ------------*/
        //1、判断有无环
        ListNode* meetingNode = MeetingNode(pHead);
        if (meetingNode == nullptr) return nullptr;
        // 2、计算环的节点数量
        int n = 1;
        ListNode* p1 = meetingNode;
        while (p1->next != meetingNode) {
            p1 = p1->next;
            n++;
        }
        /* ----------------- end ----------------*/

        /* -----------二. 找入口节点 ------------*/
        // p1 先从头移动一个环的长度
        p1 = pHead;
        for (int i = 0; i < n; i++)
            p1 = p1->next;
        // p2 从头和 p1 一块移动。相遇点就是 入口节点
        ListNode* p2 = pHead;
        while (p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }
};