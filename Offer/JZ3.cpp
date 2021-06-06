#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};

/**
 * 输入一个链表，按链表从尾到头的顺序返回一个ArrayList。
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