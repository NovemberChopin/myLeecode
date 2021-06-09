#include <iostream>
#include <structDefine.h>
using namespace std;

class Solution {
public:
    /**
     * 描述：输入一个链表，输出该链表中倒数第k个结点。如果该链表长度小于k，请返回空。
     * 输入：{1,2,3,4,5},1 
     * 输出：{5}
     * 思路：
     * 定义两个指针，一个走的快，一个走的慢
     * 快指针先走 k 步，然后两个指针一起走，直到快指针为空
     * 此时 慢指针的点就是倒数 第 k 元素
     * 
     * @param pHead ListNode类 
     * @param k int整型 
     * @return ListNode类
     */
    ListNode* FindKthToTail(ListNode* pHead, int k) {
        ListNode *pre = pHead, *nex = pHead;
        int i = 0;
        while (i < k) {
            if (nex == nullptr)
                return nullptr;
            nex = nex->next;
            i++;
        }
        while (nex) {
            pre = pre->next;
            nex = nex->next;
        }
        return pre;
    }
};