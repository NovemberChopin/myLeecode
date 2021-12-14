#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
#define MaxSize 100

typedef char Elem;
typedef struct node {
    Elem val;
    struct node* lchild;
    struct node* rchild;
} BTNode;

// 递归遍历输出二叉树节点值
void Traverse(BTNode *tree) {
    if (tree != NULL) {
        printf("%c", tree->val);
        if (tree->lchild!=NULL || tree->rchild!=NULL) {
            printf("(");
            Traverse(tree->lchild);
            if (tree->rchild!=NULL)
                printf(",");
            Traverse(tree->rchild);
            printf(")");
        }
    }
}

// void Traverse(BTNode* tree) {
//     if (tree!= NULL) {
//         // 前序遍历
//         Traverse(tree->lchild);
//         // 中序遍历
//         Traverse(tree->rchild);
//         // 后序遍历
//     }
// }

// 求二叉树的深度
int BTNodeDepth(BTNode* tree) {
    int ldeep, rdeep;
    if (tree==NULL) 
        return 0;
    else {
        ldeep = BTNodeDepth(tree->lchild);
        rdeep = BTNodeDepth(tree->rchild);
        return (ldeep > rdeep) ? (ldeep+1):(rdeep+1);
    }
}

// 计算某一个节点的深度
int getElemLevel(BTNode* tree, Elem ch, int h) {
    int deep;
    if (tree == NULL) 
        return NULL;
    else if (tree->val == ch) 
        return h;
    else {
        deep = getElemLevel(tree->lchild, ch, h+1);
        if (deep != 0) 
            return deep;
        else {
            return getElemLevel(tree->rchild, ch, h+1);
        }
    }
}


// 递归查找一个值的节点
BTNode* FindNode(BTNode* tree, Elem ch) {
    BTNode *s;
    if (tree == NULL) 
        return NULL;
    else if (tree->val == ch) 
        return tree;
    else {
        s = FindNode(tree->lchild, ch);
        if (s!=NULL)
            return s;
        else {
            return FindNode(tree->rchild, ch);
        }
    }
}

void PreOrder(BTNode* tree) {
    stack<BTNode*> st;
    BTNode* node;
    if (tree != NULL) {
        st.push(tree);
        while (!st.empty()) {
            node = st.top();
            printf("%c ", node->val);
            st.pop();
            if (node->rchild != NULL) 
                st.push(node->rchild);
            if (node->lchild != NULL)
                st.push(node->lchild);
        }
        printf("\n");
    }
}

void InOrder(BTNode *tree) {
    stack<BTNode*> st;
    if (tree == NULL) return ;
    BTNode* node = tree;
    while(!st.empty() || node != NULL) {
        while (node != NULL) {
            st.push(node);
            node = node->lchild;
        }
        if (!st.empty()) {
            node = st.top();
            printf("%c ", node->val);
            st.pop();
            node = node->rchild;
        }
    }
    printf("\n");
}

void LevalOrder(BTNode* tree) {
    BTNode* node;
    if (tree==NULL)
        return;
    queue<BTNode*> q;
    q.push(tree);
    while(!q.empty()) {
        node = q.front();
        printf("%c ", node->val);
        q.pop();
        if (node->lchild)
            q.push(node->lchild);
        if (node->rchild)
            q.push(node->rchild);
    }
    printf("\n");
}






BTNode* LChildNode(BTNode *tree) {
    return tree->lchild;
}