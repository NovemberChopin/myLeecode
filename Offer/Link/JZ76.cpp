
#include <unordered_set>

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
    ListNode* deleteDuplication(ListNode* pHead) {
        // 使用 hash 表
//         if (!pHead) return pHead;
//         unordered_set<int> st;
//         ListNode *pre = pHead;
//         ListNode *cur = pHead->next;
//         while (cur) {
//             if (pre->val == cur->val)
//                 st.insert(pre->val);
//             pre = pre->next;
//             cur = cur->next;
//         }
//         // 再次遍历链表
//         ListNode* vhead = new ListNode(-1);
//         pre = vhead;
//         cur = pHead;
//         while(cur) {
//             if (st.count(cur->val)) {
//                 cur = cur->next;
//             } 
//             else {
//                 pre->next = cur;
//                 pre = cur;
//                 cur = cur->next;
//             }
//             pre->next = NULL;
//         }
//         return vhead->next;
        
        // 直接删除(双指针法)
        ListNode *vhead = new ListNode(-1);
        vhead->next = pHead;
        ListNode *pre = vhead, *cur = pHead;
        while (cur) {
            if (cur->next && cur->val == cur->next->val) {
                cur = cur->next;
                while (cur->next && cur->val == cur->next->val) {
                    cur = cur->next;
                }
                pre->next = cur->next;
                cur = cur->next;
            }
            else {
                pre = cur;
                cur = cur->next;
            }
        }
        return vhead->next;
    }
};
