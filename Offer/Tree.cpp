#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>

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
     * JZ26 树的子结构
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
     * JZ27: 求二叉树的镜像
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
    // 前序遍历（用栈）
    TreeNode* Mirror(TreeNode* pRoot) {
        stack<TreeNode*> st;
        if (!pRoot) return NULL;
        TreeNode* node, *temp;
        st.push(pRoot);
        while(!st.empty()) {
            node = st.top();
            st.pop();
            // 交换左右节点指针
            temp = node->left;
            node->left = node->right;
            node->right = temp;
            
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
        return pRoot;
    }



    /**
     * JZ32: 从上往下打印二叉树
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
     * JZ34 二叉树中和为某一值的路径
     * 输入一颗二叉树的根节点和一个整数，按字典序打印出二叉树中结点值
     * 的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到
     * 叶结点所经过的结点形成一条路径
     * 输入：{10,5,12,4,7},22
     * 输出：[[10,5,7],[10,12]]
     * 思路：递归
     */ 
    vector<vector<int>> res;
    vector<int> path;
    void find(TreeNode* root, int sum) {
        if (root == nullptr) 
            return;
        path.push_back(root->val);
        if (!root->left && !root->right && sum == root->val) 
            res.push_back(path);
        else {
            if (root->left) find(root->left, sum - root->val);
            if (root->right) find(root->right, sum - root->val);
        }
        path.pop_back();
    }
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        find(root, expectNumber);
        return res;
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
     * JZ54 二叉搜索树的第 k 个节点
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


    /**
     * JZ54 二叉搜索数的第K个节点
     * 
     *代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 
     * @param proot TreeNode类 
     * @param k int整型 
     * @return int整型
     */
    int count = 0;    // 遍历的节点数
    int result = -1;
    int KthNode2(TreeNode* proot, int k) {
        // write code here
        stack<TreeNode*> st;
        TreeNode* node = proot;
        vector<int> vt;
        if (!proot || k==0) return -1;
        while(!st.empty() || node != NULL) {
            while(node != NULL) {
                st.push(node);
                node = node->left;
            }
            if (!st.empty()) {
                node = st.top();
                vt.push_back(node->val);
                st.pop();
                node = node->right;
            }
        }
        if (k > vt.size())
            return -1;
        else return vt[k-1];
        
        // 中序遍历不需要list存储
        stack<TreeNode*> st;
        TreeNode* node = proot;
        int i = 0;
        if (!proot || k==0) return -1;
        while(!st.empty() || node != NULL) {
            while(node != NULL) {
                st.push(node);
                node = node->left;
            }
            if (!st.empty()) {
                node = st.top();
                i++;
                if (i==k) return node->val;
                st.pop();
                node = node->right;
            }
        }
        return -1;
        
        // 递归版本
        if (proot == NULL || k <= 0)    return -1;
        KthNode2(proot->left, k);
        count++;
        if (count == k)    return result = proot->val;
        KthNode2(proot->right, k);
        return result;
    }



    //
    //  JZ7 重建二叉树
    //  根据前序和中序重建二叉树
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        int vinlen = vin.size();
        if (vinlen==0)    return NULL;
        vector<int> pre_left, pre_right, vin_left, vin_right;
        // 创建根节点 -> 前序遍历第一个数
        TreeNode* head = new TreeNode(pre[0]);
        // 找到中序遍历根节点的位置，存放在 gen 中
        int gen = 0;
        for (int i = 0; i < vinlen; i++) {
            if (vin[i] == pre[0]) {
                gen = i;
                break;
            }
        }
        // 对于中序遍历，根节点左边的节点位于二叉树的左边，
        // 根节点右边的节点位于二叉树的右边
        for (int i = 0; i < gen; i++) {    // 左子树
            vin_left.push_back(vin[i]);
            pre_left.push_back(pre[i+1]);    //先序第一个为根节点
        }
        for (int i = gen+1; i < vinlen; i++) {    // 右子树
            vin_right.push_back(vin[i]);
            pre_right.push_back(pre[i]);
        }
        // 递归，执行上述步骤，直到根节点
        head->left = reConstructBinaryTree(pre_left, vin_left);
        head->right = reConstructBinaryTree(pre_right, vin_right);
        return head;
    }

    /**
     * JZ33 二叉搜索树的后续遍历序列
     * 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
     */
    // 方法一：递归法：后续遍历最后一个数为根节点，
    // 根据根节点大小划分左右节点，判断左子树是否都小于根节点和
    // 右子树是否大于根节点
    bool VerifySquenceOfBST(vector<int> sequence) {
        int sz = sequence.size();
        if (sz == 0)
            return false;
        return check(sequence, 0, sz-1);
    }
    bool check(vector<int> sequence, int l, int r) {
        if (l >= r)    // 若当前子树只有一个节点
            return true;
        int root = sequence[r];
        // 划分出右子树
        int j = r - 1;
        while (j >= 0 && sequence[j] > root)
            j--;
        // 检查左子树是不是存在大于根节点的节点
        for (int i = l; i <= j; i++) {
            if (sequence[i] > root)
                return false;
        }
        return check(sequence, l, j) && check(sequence, j+1, r-1);
    }
    // 方法二：使用栈
    // 二叉树的中序遍历和后序遍历对应着一种栈的压入、弹出序列, 
    // 而对后序遍历序列从小到大排序就得到了中序遍历序列
    bool VerifySquenceOfBST(vector<int> sequence) {
        if (sequence.empty()) return false;
        vector<int> inOrder(sequence);
        // 对后序序类进行排序得到中序序列
        sort(inOrder.begin(), inOrder.end());
        
        // 验证 sequence 是否为 inOrder 的一种出栈序列
        stack<int> st;
        int i = 0, j = 0;
        for (i = 0; i < inOrder.size(); i++) {
            st.push(inOrder[i]);
            while (!st.empty() && st.top() == sequence[j]) {
                st.pop();
                j++;
            }
        }
        return st.empty();
    }

    /**
     * JZ36 二叉搜索树与双向链表
     * 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。如下图所示
     * 中序非递归遍历，期间后插建表
     */
    TreeNode* Convert(TreeNode* pRootOfTree) {
        stack<TreeNode*> st;
        TreeNode *node = pRootOfTree;
        TreeNode *Link = new TreeNode(-1);
        TreeNode *rear = Link;
        if (node == NULL)
            return node;
        while (!st.empty() || node) {
            while (node) {
                st.push(node);
                node = node->left;
            }
            if (!st.empty()) {
                node = st.top();
                st.pop();
                rear->right = node;
                node->left = rear;
                rear = node;
                node = node->right;
            }
        }
        rear->right = NULL;
        // 去掉第一个头节点
        Link = Link->right;
        free(Link->left);
        Link->left = NULL;
        return Link;
    }

    /**
     * JZ79 判断是不是平衡二叉树
     * 输入一棵节点数为 n 二叉树，判断该二叉树是否是平衡二叉树。
     * 思路：用map存储所有节点的高度，然后递归判断
     */
    map<TreeNode*, int> hs;
    // 使用 hash 表来存储每一个节点的高度，然后利用高度来判断
    int depth(TreeNode *root) {
        if (!root)
            return 0;
        if (hs.find(root) != hs.end())
            return hs[root];
        int ldeep = depth(root->left);
        int rdeep = depth(root->right);
        return hs[root] = max(ldeep, rdeep) + 1;
    }
    bool judge(TreeNode* root) {
        if (!root) return true;
        return abs(hs[root->left] - hs[root->right]) <= 1 && judge(root->left) && judge(root->right);
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
        depth(pRoot);
        return judge(pRoot);
    }


    /**
     * JZ8 二叉树的下一个结点
     */
    struct TreeLinkNode {
        int val;
        struct TreeLinkNode *left;
        struct TreeLinkNode *right;
        struct TreeLinkNode *next;
        TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {}
    };
    void pre_order(TreeLinkNode *root, vector<TreeLinkNode*> &v) {
        if (!root) return;
        pre_order(root->left, v);
        v.push_back(root);
        pre_order(root->right, v);
    }
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        TreeLinkNode *root = nullptr;
        TreeLinkNode *tmp = pNode;
        // 1、求出根节点
        while (tmp) {
            root = tmp;
            tmp = tmp->next;
        }
        // 2、递归遍历
        vector<TreeLinkNode*> v;
        pre_order(root, v);
        // 3、在 vector 中找到根节点的下一个节点
        int n = v.size();
        for (int i = 0; i < n; i++) {
            if (v[i] == pNode && i + 1 != n)
                return v[i+1];
        }
        return nullptr;
    }

    /**
     * JZ28 对称的二叉树 
     * 给定一棵二叉树，判断其是否是自身的镜像（即：是否对称）
     */
    // 方法一：使用递归
    bool isSame(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) // 均为空节点：符合 “对称” 要求；
            return true;
        if (!root1 || !root2) // 其中一个节点为空，不符合 “对称” 要求；
            return false;
        return root1->val == root2->val && isSame(root1->left, root2->right) && isSame(root1->right, root2->left);
    }
    bool isSymmetrical(TreeNode* pRoot) {
        return isSame(pRoot, pRoot);
    }
    
    // 使用层次遍历
    bool check(vector<TreeNode*> vec) {
        int i = 0, j = vec.size()-1;
        while (i < j) {
            if (vec[i]->val != vec[j]->val)
                return false;
            i++;
            j--;
        }
        return true;
    }
    bool isSymmetrical2(TreeNode* pRoot) {
        queue<TreeNode*> qu;
        TreeNode* node;
        TreeNode* empytNode = new TreeNode(-1);
        vector<TreeNode*> vec;
        if (!pRoot) return true;
        qu.push(pRoot);
        while(!qu.empty()) {
            int size = qu.size();
            while (size--) {
                node = qu.front();
                vec.push_back(node);
                qu.pop();
                if (node->val != empytNode->val) {
                    if (node->left) qu.push(node->left);
                    else qu.push(empytNode);
                    if (node->right) qu.push(node->right);
                    else qu.push(empytNode);
                }
            }
            if (!check(vec)) return false;
            vec.clear();
        }
        return true;
    }
};