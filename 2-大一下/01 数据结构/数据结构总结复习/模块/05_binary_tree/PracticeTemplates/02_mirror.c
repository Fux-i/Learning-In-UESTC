/*
 * 题目：镜像二叉树
 * 来源：真题179
 * 要求：生成二叉树的镜像二叉树
 *
 * 镜像定义：左右子树交换
 *
 * 函数声明：
 *   btree mirror(btree tree);
 *
 * 参数说明：
 *   tree: 指向源二叉树根结点的指针
 *
 * 返回值：
 *   指向镜像二叉树根结点的指针
 *
 * TODO: 补全 mirror 函数
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _btree_node {
    char tag;  // 结点标签
    struct _btree_node *left;
    struct _btree_node *right;
} btree_node, *btree;

// 创建新结点
btree create_node(char tag) {
    btree node = (btree)malloc(sizeof(btree_node));
    node->tag = tag;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 先序遍历
void pre_order(btree root) {
    if (root == NULL) return;
    printf("%c ", root->tag);
    pre_order(root->left);
    pre_order(root->right);
}

// TODO: 补全镜像操作
// 生成一棵新的镜像二叉树
// 提示：递归交换左右子树
btree mirror(btree tree) {
    // TODO: 在此补全代码

}

int main() {
    // 构造测试二叉树
    //     A
    //    / \
    //   B   C
    //  / \
    // D   E
    btree root = create_node('A');
    root->left = create_node('B');
    root->right = create_node('C');
    root->left->left = create_node('D');
    root->left->right = create_node('E');

    printf("原树先序遍历：");
    pre_order(root);
    printf("\n");
    // 预期输出：A B D E C

    btree mirror_tree = mirror(root);
    printf("镜像树先序遍历：");
    pre_order(mirror_tree);
    printf("\n");
    // 预期输出：A C B E D

    return 0;
}
