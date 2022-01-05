

#include <iostream>
#include <unordered_map>
using namespace std;

/**
 * JZ35 复杂链表的复制
 * 
 */ 

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        if (!pHead) return pHead;
        unordered_map<RandomListNode*, RandomListNode*> mp;
        RandomListNode* dummy = new RandomListNode(-1);
        // 后插入创建链表
        RandomListNode* pre=dummy, *cur=pHead;
        while (cur) {
            RandomListNode* clone = new RandomListNode(cur->label);
            pre->next = clone;
            mp[cur] = clone;    // 记录映射关系
            pre = pre->next;
            cur = cur->next;
        }
        for (auto& [key, value] : mp) {    // 遍历哈希表
            value->random = key->random == NULL ? NULL : mp[key->random];
        }
        return dummy->next;
    }
};
