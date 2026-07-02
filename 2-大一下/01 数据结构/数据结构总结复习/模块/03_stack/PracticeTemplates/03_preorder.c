/*
 * 题目：非递归先序遍历
 * 来源：23级二轮、24级三批、真题120、真题198
 * 要求：用栈实现二叉树的非递归先序遍历
 *
 * 函数声明：
 *   void pre_order(BiTree root);
 *
 * 参数说明：
 *   root: 指向二叉树根结点的指针
 *
 * 关键逻辑：
 *   1. 根结点入栈
 *   2. 循环：弹出栈顶并访问
 *   3. 先右子树入栈，再左子树入栈（保证左子树先被访问）
 *
 * TODO: 补全 pre_order 函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 二叉树结点定义
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} BiTNode, *BiTree;

// 栈定义
#define Stack_Size 50

typedef BiTNode* ElemType;

typedef struct {
    ElemType elem[Stack_Size];
    int top;
} Stack;

void init_stack(Stack *S) {
    S->top = -1;
}

bool is_empty(Stack *S) {
    return S->top == -1;
}

bool push(Stack *S, ElemType x) {
    if (S->top >= Stack_Size - 1) return false;
    S->elem[++S->top] = x;
    return true;
}

bool pop(Stack *S, ElemType *px) {
    if (S->top == -1) return false;
    *px = S->elem[S->top--];
    return true;
}

// 访问结点
void visit(BiTNode *node) {
    printf("%d ", node->data);
}

// 创建新结点
BiTree create_node(int data) {
    BiTree node = (BiTree)malloc(sizeof(BiTNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// TODO: 补全非递归先序遍历
// 要求：使用栈实现，不能使用递归
void pre_order(BiTree root) {
    // TODO: 在此补全代码

}

int main() {
    // 构造测试二叉树
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    BiTree root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);

    printf("先序遍历结果：");
    pre_order(root);
    printf("\n");
    // 预期输出：1 2 4 5 3

    return 0;
}
