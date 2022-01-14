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
    node(int x):
		val(x), lchild(NULL), rchild(NULL) {}
} BTNode;

/**
 * Create binary from str
 * @param str: character array
 */
void CreateBinaryTree(BTNode *&tree, char *str) {
    BTNode *stack[MaxSize], *s = NULL;
    int top = -1, i = 0, k;
    char ch = str[i];
    tree = NULL;
    while (ch!='\0') {
        switch (ch) {
            case '(': // k = 1: the next char is lchild
                top++; stack[top]=s; k = 1; break;
            case ')': 
                top--; break;
            case ',':   // k=2: the next char is rchild
                k=2; break;
            default:
                s = (BTNode*)malloc(sizeof(BTNode));
                s->val = ch;
                s->lchild = s->rchild = NULL;
                if (tree == NULL) tree = s;
                else {
                    switch(k) {
                        case 1: stack[top]->lchild = s; break;
                        case 2: stack[top]->rchild = s; break;
                    }
                }
        }
        i++;
        ch = str[i];
    }   
}

void Traverse(BTNode *tree) {
    if (tree != NULL) {
        printf("%c",tree->val);
		if (tree->lchild!=NULL || tree->rchild!=NULL)
		{
			printf("(");
			Traverse(tree->lchild);
			if (tree->rchild!=NULL) printf(",");
			Traverse(tree->rchild);
			printf(")");
		}
    }
}

BTNode* LChildNode(BTNode *tree) {
    return tree->lchild;
}

BTNode* RChildNode(BTNode *tree) {
    return tree->rchild;
}

/* -------------- Traverse tree by recursion method ----------------*/

// void Traverse(BTNode *tree) {
//     if (tree!=NULL) {
//         // preOrder
//         Traverse(tree->lchild);
//         // inOrder
//         Traverse(tree->rchild);
//         // postOrder
//     }
// }

BTNode* FindNode(BTNode *tree, Elem ch) {
    BTNode *s;
    if (tree == NULL) {
        return NULL;
    } else if (tree->val == ch) {
        return tree;
    } else {
        s = FindNode(tree->lchild, ch);
        if (s != NULL)
            return s;
        else 
            return FindNode(tree->rchild, ch);
    }
}

/**
 * get the depth of the tree.
 */
int BTNodeDepth(BTNode *tree) {
    int lDeep, rDeep;
    if (tree == NULL)
        return 0;
    else {
        lDeep = BTNodeDepth(tree->lchild);
        rDeep = BTNodeDepth(tree->rchild);
        return (lDeep > rDeep)? (lDeep+1):(rDeep+1);
    }
}

/**
 * get the element x's depth in the tree
 * @param h: the level of the node tree. init is 1
 */
int getElemLevel(BTNode *tree, Elem ch, int h) {
    int lDeep;
    if (tree == NULL)
        return 0;
    else if (tree->val == ch)
        return h;
    else {
        lDeep = getElemLevel(tree->lchild, ch, h+1);
        if (lDeep != 0)
            return lDeep;
        else 
            return getElemLevel(tree->rchild, ch, h+1);
    }
}

/**
 * get the number of node in the tree
 */
int NodeNum(BTNode *tree) {
    int lNum, rNum;
    if (tree == NULL)
        return 0;
    else if (tree->lchild==NULL && tree->rchild==NULL)
        return 1;
    else {
        lNum = NodeNum(tree->lchild);
        rNum = NodeNum(tree->rchild);
        return (lNum+rNum+1);
        /* get the number of leaf nodes */
        // return (lNum+rNum+1);
    }
}

void DistroyBinaryTree(BTNode *&tree) {
    if (tree != NULL) {
        DistroyBinaryTree(tree->lchild);
        DistroyBinaryTree(tree->rchild);
        free(tree);
    }
}

/* ----------------------------- end --------------------------------*/

/* -------------------- Non-recursion Traverse ----------------------*/

// void PreOrder(BTNode *tree) {
//     BTNode *stack[MaxSize], *s;
//     int top = -1;
//     if (tree != NULL) {
//         top++;
//         stack[top] = tree;
//         while (top > -1) {
//             s = stack[top];
//             top--;
//             printf("%c ", s->val);
//             if (s->rchild != NULL) { // rchild push first
//                 top++;
//                 stack[top] = s->rchild;
//             }
//             if (s->lchild != NULL) {
//                 top++;
//                 stack[top] = s->lchild;
//             }
//         }
//         printf("\n");
//     }
// }

void PreOrder(BTNode *tree) {
    stack<BTNode*> st;
    BTNode *node;
    if (tree != NULL) {
        st.push(tree);
        while (!st.empty()) {
            node = st.top();
            st.pop();
            printf("%c ", node->val);
            if (node->rchild != NULL)
                st.push(node->rchild);
            if (node->lchild != NULL)
                st.push(node->lchild);
        }
        printf("\n");
    }
}

// void InOrder(BTNode *tree) {
//     BTNode *stack[MaxSize], *s;
//     int top = -1;
//     if (tree != NULL) {
//         s = tree;
//         while (top > -1 || s != NULL) { // 处理 *s 节点的左子树
//             while (s != NULL) { // 扫描 *s 的所有左节点并进栈
//                 top++;
//                 stack[top] = s;
//                 s = s->lchild;
//             }
//             // 此时栈顶元素没有左边孩子 或左子树 均已访问过
//             if (top > -1) {
//                 s = stack[top];
//                 top--;
//                 printf("%c ", s->val);
//                 s = s->rchild;  // 处理 *s 的右孩子节点
//             }
//         }
//         printf("\n");
//     }
// }

void InOrder(BTNode* tree) {
    stack<BTNode*> st;
    if (tree == nullptr) return;
    BTNode* node = tree;
    while (!st.empty() || node != nullptr) {
        while (node != nullptr) {
            st.push(node);
            node = node->lchild;
        }
        if (!st.empty()) {
            node = st.top();
            st.pop();
            printf("%c ", node->val);
            node = node->rchild;
        }
    }
    printf("\n");
}


// void LevelOrder(BTNode *tree) {
//     BTNode *p, *queue[MaxSize];
//     int front = 0, rear = 0;
//     rear++;
//     queue[rear] = tree;
//     while (front != rear) { // queue is not empty
//         front = (front + 1) % MaxSize;  // DeQueue
//         p = queue[front];
//         printf("%c ", p->val);
//         if (p->lchild != NULL) {
//             rear = (rear + 1) % MaxSize;
//             queue[rear] = p->lchild;
//         }
//         if (p->rchild != NULL) {
//             rear = (rear + 1) % MaxSize;
//             queue[rear] = p->rchild;
//         }
//     }
//     printf("\n");
// }


void LevelOrder(BTNode *tree) {
    // 层次遍历，同时可以统计数的深度
    BTNode *node=tree;
    queue<BTNode*> q;
    if (!tree) return;
    q.push(node);
    int level = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            node = q.front();
            q.pop();
            printf("%c ", node->val);
            if (node->lchild != NULL)
                q.push(node->lchild);
            if (node->rchild != NULL)
                q.push(node->rchild);
        }
        level++;
    }
    printf(" level is %d \n", level);
}

/* ----------------------------- end --------------------------------*/


/**
 * Create BinaryTree from preOrder and inOrder (使用指针)
 */ 
BTNode *CreateBTFromPreAndIn(char *pre, char *in, int n) {
    BTNode *b;
    char *p;
    int k;
    if (n <= 0) return nullptr;
    b = (BTNode*)malloc(sizeof(BTNode));
    b->val = *pre;
    for (p = in; p < in + n; p++)       // 在中序序列中找到 *pre 的节点位置 k
        if (*p == *pre)                 // pre 指向根节点
            break;                      // 在 in 中找到后退出循环
    k = p - in;                         // 确定根节点在 in 中的位置（下标）
    b->lchild = CreateBTFromPreAndIn(pre+1, in, k);    
    // p+1: p 指向中序的根节点，p+1就是右子树的中序。右子树的长度就是 减去左子树和根节点长度
    b->rchild = CreateBTFromPreAndIn(pre+k+1, p+1, n-k-1);
    return b;
}

// 使用前序和中序数组重建二叉树
BTNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
    int vinlen = vin.size();
    if (vinlen==0)    return NULL;
    vector<int> pre_left, pre_right, vin_left, vin_right;
    // 创建根节点 -> 前序遍历第一个数
    BTNode* head = new BTNode(pre[0]);
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
    head->lchild = reConstructBinaryTree(pre_left, vin_left);
    head->rchild = reConstructBinaryTree(pre_right, vin_right);
    return head;
}


int main() {
    BTNode *tree,*p,*lp,*rp;;
    char str[] = {"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"};
    char str2[] = {"A(B(D,E),C(F,G))"};
	CreateBinaryTree(tree, str2);
	printf("(1):Display binary tree:");
    Traverse(tree);
    printf("\n");
    p=FindNode(tree,'H');
	if (p!=NULL)
	{	lp=LChildNode(p);
		if (lp!=NULL)
			printf("(2):Left child is %c\n",lp->val);
		else
			printf("(2):No left child.\n");
		rp=RChildNode(p);
		if (rp!=NULL)
			printf("(3):Right child is %c\n",rp->val);
		else
			printf("(3):No right child.\n");
	}
    printf("(4):The depth of the tree is %d\n", BTNodeDepth(tree));
    printf("(5):The number of nodes in the tree is %d\n", NodeNum(tree));
    printf("(6):The level of element L is %d\n", getElemLevel(tree, 'L', 1));
    printf("(7):PreOrder with Non-recursion method:");
    PreOrder(tree);
    printf("(8):InOrder with Non-recursion method:");
    InOrder(tree);
    printf("(9):LevelOrder squence is:");
    LevelOrder(tree);

    char preOrder[] = {"ABDGCEF"};
    char inOrder[] = {"DGBAECF"};
    BTNode *tree2  = CreateBTFromPreAndIn(preOrder, inOrder, 7);
    printf("(10):Create Binary tree2 from preOrder and inOrder, preOrder is:");
    PreOrder(tree2);

    printf("(11):Destroy binary tree\n");
    DistroyBinaryTree(tree);
    DistroyBinaryTree(tree2);
    return 0;
}