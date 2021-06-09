#include <iostream>
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
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
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
};