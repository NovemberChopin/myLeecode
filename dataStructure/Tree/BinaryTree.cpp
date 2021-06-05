#include <stdio.h>
#include <malloc.h>
#define MaxSize 100

typedef char Elem;
typedef struct node {
    Elem val;
    struct node* lchild;
    struct node* rchild;
} BTNode;


void CreateBinaryTree(BTNode *&tree, char *str) {
    BTNode *stack[MaxSize], *s = NULL;
    int top = -1, i = 0, k;
    char ch = str[i];
    tree = NULL;
    while (ch!='\0') {
        switch (ch) {
            case '(': 
                // k = 1: the next char is lchild
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

/* ----------- Traverse tree by recursion method -------------*/

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

/* -------------------- recursion method ----------------------*/




int main() {
    BTNode *b,*p,*lp,*rp;;
    char str[] = {"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"};
	CreateBinaryTree(b, str);
	printf("Display binary tree:");
    Traverse(b);
    printf("\n");
    p=FindNode(b,'H');
	if (p!=NULL)
	{	lp=LChildNode(p);
		if (lp!=NULL)
			printf("Left child is %c\n",lp->val);
		else
			printf("No left child.\n");
		rp=RChildNode(p);
		if (rp!=NULL)
			printf("Right child is %c\n",rp->val);
		else
			printf("No right child.\n");
	}
    printf("The depth of the tree is %d\n", BTNodeDepth(b));
    printf("The number of nodes in the tree is %d\n", NodeNum(b));
    printf("The level of element L is %d\n", getElemLevel(b, 'L', 1));
    printf("Destroy binary tree\n");
    DistroyBinaryTree(b);
    return 0;
}