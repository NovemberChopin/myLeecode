#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>

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
     * JZ17 树的子结构
     * 输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
     * 输入：{8,8,#,9,#,2,#,5},{8,9,#,2}
     * 输出：true
     * 思路：以每个节点为根节点，分别判断是否为子树
     */
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if (pRoot1==nullptr || pRoot2==nullptr)
            return false;
        return isSubtree(pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    }
    bool isSubtree(TreeNode* b1, TreeNode* b2) {
        if (b2 == nullptr)  return true;
        //此处为p2 == null 是匹配完成的条件
        //最开始p2肯定不为NULL,这是在主程序HasSubtree中判断过的。
        //递归中，如果p2为空了，则表示上一层的递归中的p2已经匹配完了
        if (b1 == nullptr) return false;
        return b1->val == b2->val && isSubtree(b1->left, b2->left) && isSubtree(b1->right, b2->right);
    }

    
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
     * 从上往下打印出二叉树的每个节点，同层节点从左至右打印。
     * 思路：层次遍历
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
    }
    /* ----------------- 调用队列库实现 ----------------- */   
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> list;
        TreeNode* p;
        if (!root) return list;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            // 取出队头元素，加入 vector 容器中
            p = q.front();
            list.push_back(p->val);
            q.pop();
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        return list;
    }

    

    /**
     * JZ38 二叉树的深度
     * 输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点
     * （含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
     * 输入：{1,2,3,4,5,#,6,#,#,7}
     * 输出：4
     */
    /*------------- 递归方法 ------------------*/
    int TreeDepth(TreeNode* pRoot) {
        if (!pRoot)
            return 0;
        int ld = TreeDepth(pRoot->left);
        int rd = TreeDepth(pRoot->right);
        return (max(ld, rd)+1);
    }
    /*------------- 非递归方法 - 队列------------------*/
    int TreeDepth(TreeNode* pRoot) {
        if (!pRoot) return 0;
        int level = 0;
        TreeNode* node;
        queue<TreeNode*> que;
        que.push(pRoot);
        while(!que.empty()) {
            int size = que.size();
            while (size--) {
                node = que.front();
                que.pop();
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            level++;
        }
        return level;
    }

    /**
     * JZ59 按之字型打印二叉树
     * 输入：{8,6,10,5,7,9,11}
     * 输出：[[8],[10,6],[5,7,9,11]]
     * 思路：层序遍历，使用队列
     */
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int>> barray;
        vector<int> temp;    // 存储每一层的数据
        int level = 0;
        if (!pRoot) return barray;
        TreeNode* node;
        queue<TreeNode*> que;
        que.push(pRoot);
        while(!que.empty()) {
            int size = que.size();
            while (size--) {
                node = que.front();
                temp.push_back(node->val);
                que.pop();
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            if (level % 2 == 1)    // 偶数层反转
                reverse(temp.begin(), temp.end());
            barray.push_back(temp);
            temp.clear();
            level++;
        }
        return barray;
    }


    /**
     * JZ62 二叉搜索树的第 k 个节点
     * 给定一棵二叉搜索树，请找出其中的第k小的TreeNode结点。
     * 输入：{5,3,7,2,4,6,8},3
     * 输出：{4}
     * 思路：中序遍历：递归和非递归法
     */
    TreeNode* KthNode(TreeNode* pRoot, int k) {
        //中序遍历的结果就是有序序列，第K个元素就是vec[K-1]存储的节点指针；
        if (pRoot == nullptr || k <= 0) return nullptr;
        vector<TreeNode*> vec;
        InOrder(pRoot, vec);
        if (k > vec.size()) return nullptr;
        return vec[k-1];
    }
    void InOrder(TreeNode* pRoot, vector<TreeNode*>& vec) {
        if (pRoot == nullptr) return;
        InOrder(pRoot->left, vec);
        vec.push_back(pRoot);
        InOrder(pRoot->right, vec);
    }
    /* 方法二：使用非递归方法（栈） */
    TreeNode* KthNode(TreeNode* pRoot, int k) {
        if (pRoot == nullptr || k <= 0) 
            return nullptr;
        stack<TreeNode*> st;
        TreeNode* node = pRoot;
        int num = 0;
        while (!st.empty() || node != nullptr) {
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }
            if (!st.empty()) {
                node = st.top();
                st.pop();
                num++;
                if (num == k) return node;
                node = node->right;
            }
        }
        return nullptr;
    }
};