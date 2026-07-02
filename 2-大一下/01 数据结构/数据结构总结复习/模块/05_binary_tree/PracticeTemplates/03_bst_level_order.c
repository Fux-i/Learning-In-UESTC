/*
 * 题目：二叉排序树构建与层序遍历
 * 来源：真题162
 * 要求：
 *   1. 根据输入数组构建二叉排序树（BST）
 *   2. 对 BST 进行层序遍历
 *
 * 函数声明：
 *   void check_tree_level_visit(int keys[], int n);
 *
 * 参数说明：
 *   keys: 输入的关键字数组
 *   n: 数组长度
 *
 * 示例：
 *   输入：[36, 53, 28, 68, 9, 33]
 *   输出：[36, 28, 53, 9, 33, 68]
 *
 * TODO: 补全 BST 插入和层序遍历
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node, *tree;

// 创建新结点
tree create_node(int data) {
    tree node = (tree)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// TODO: 补全 BST 插入操作
// 提示：递归插入，小于当前结点插入左子树，大于插入右子树
tree bst_insert(tree root, int value) {
    // TODO: 在此补全代码

}

// TODO: 补全层序遍历
// 提示：使用数组模拟队列
void level_order(tree root, int result[], int *n) {
    // TODO: 在此补全代码

}

// 主函数
void check_tree_level_visit(int keys[], int n) {
    if (n <= 0) return;

    // 构建 BST
    tree root = create_node(keys[0]);
    for (int i = 1; i < n; i++) {
        bst_insert(root, keys[i]);
    }

    // 层序遍历
    int result[100];
    int count = 0;
    level_order(root, result, &count);

    // 输出结果
    printf("层序遍历结果：");
    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int keys[] = {36, 53, 28, 68, 9, 33};
    int n = 6;

    printf("输入序列：");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
    }
    printf("\n");

    check_tree_level_visit(keys, n);
    // 预期输出：36 28 53 9 33 68

    return 0;
}
