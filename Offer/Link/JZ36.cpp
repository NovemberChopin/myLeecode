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
    int GetListLength(ListNode* list) {
        ListNode* p = list;
        int length = 0;
        while (p) {
            ++length;
            p = p->next;
            
        }
        return length;
    }
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        // 思路一：用栈
        // 思路二：先计算两个链表的长度之差。然后在较长链表上提前走若干步，然后使用双链表，
        //        第一个相同元素就是第一个公共节点
        ListNode *p1 = pHead1, *p2=pHead2;
        int length1 = GetListLength(pHead1);
        int length2 = GetListLength(pHead2);
        int lengthDiff = length1 - length2;
        if (length1 < length2) {
            p1 = pHead2;
            p2 = pHead1;
            lengthDiff = length2 - length1;
        }
        for (int i = 0; i < lengthDiff; i++)
            p1 = p1->next;
        while (p1!=nullptr && p2!=nullptr && p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }
};