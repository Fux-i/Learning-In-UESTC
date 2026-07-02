/*
 * 题目：递归先序遍历
 * 来源：23级、原 Todo
 * 要求：实现二叉树的递归先序遍历
 *
 * 函数声明：
 *   void pre_order(BiTree root);
 *
 * 参数说明：
 *   root: 指向二叉树根结点的指针
 *
 * 遍历顺序：根 -> 左 -> 右
 *
 * TODO: 补全 pre_order 函数
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} BiTNode, *BiTree;

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

// TODO: 补全递归先序遍历
// 顺序：根 -> 左 -> 右
void pre_order(BiTree root) {
    // TODO: 在此补全代码

}

// 递归中序遍历（供参考）
void in_order(BiTree root) {
    if (root == NULL) return;
    in_order(root->left);
    visit(root);
    in_order(root->right);
}

// 递归后序遍历（供参考）
void post_order(BiTree root) {
    if (root == NULL) return;
    post_order(root->left);
    post_order(root->right);
    visit(root);
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

    printf("先序遍历：");
    pre_order(root);
    printf("\n");
    // 预期输出：1 2 4 5 3

    printf("中序遍历：");
    in_order(root);
    printf("\n");
    // 预期输出：4 2 5 1 3

    printf("后序遍历：");
    post_order(root);
    printf("\n");
    // 预期输出：4 5 2 3 1

    return 0;
}
