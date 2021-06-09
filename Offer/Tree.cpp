#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
class Solution {
public:
    /**
     * JZ18: 求二叉树的镜像
     *
     * @param pRoot TreeNode类 
     * @return TreeNode类
     */
    TreeNode* Mirror(TreeNode* pRoot) {
        TreeNode *pl, *pr;
        if (pRoot == nullptr)
            return pRoot;
        pl = Mirror(pRoot->left);
        pr = Mirror(pRoot->right);
        pRoot->left = pr;
        pRoot->right = pl;
        return pRoot;
    }

    /**
     * JZ22: 从上往下打印二叉树
     */
    vector<int> PrintFromTopToBottom(TreeNode* root) {
    //-----------------手动实现队列-----------------
        vector<int> list;
        if (!root) return list;
        int MaxSize = 100;
        TreeNode* p;
        TreeNode* queue[MaxSize];
        int front, rear;
        front = rear = 0;
        rear = (rear + 1) % MaxSize;
        queue[rear] = root;
        while (front != rear) {
            front = (front + 1) % MaxSize;
            p = queue[front];
            list.push_back(p->val);
            if (p->left) {
                rear = (rear + 1) % MaxSize;
                queue[rear] = p->left;
            }
            if (p->right) {
                rear = (rear + 1) % MaxSize;
                queue[rear] = p->right;
            }
        }
        return list;
// ----------------- 调用队列库实现 -----------------        
//         vector<int> list;
//         TreeNode* p;
//         if (!root) return list;
//         queue<TreeNode*> q;
//         q.push(root);
//         while (!q.empty()) {
//             // 取出队头元素，加入 vector 容器中
//             p = q.front();
//             list.push_back(p->val);
//             q.pop();
//             if (p->left) q.push(p->left);
//             if (p->right) q.push(p->right);
//         }
//         return list;
    }
};