/*
 * 题目：层序遍历二叉树
 * 来源：23级一轮、真题162、真题180
 * 要求：使用队列实现二叉树的层序遍历
 *
 * 函数声明：
 *   void level_order(BiTree root);
 *
 * 参数说明：
 *   root: 指向二叉树根结点的指针
 *
 * 关键逻辑：
 *   1. 根结点入队
 *   2. 循环：出队并访问，将子结点入队
 *
 * TODO: 补全 level_order 函数
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

// 队列定义
#define MAXSIZE 50

typedef BiTNode* QElemType;

typedef struct {
    QElemType elem[MAXSIZE];
    int front;
    int rear;
} SqQueue;

void init_queue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
}

bool is_empty(SqQueue *Q) {
    return Q->front == Q->rear;
}

bool enter_queue(SqQueue *Q, QElemType x) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) return false;
    Q->elem[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return true;
}

bool leave_queue(SqQueue *Q, QElemType *px) {
    if (is_empty(Q)) return false;
    *px = Q->elem[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
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

// TODO: 补全层序遍历
// 要求：使用队列实现
void level_order(BiTree root) {
    // TODO: 在此补全代码

}

int main() {
    // 构造测试二叉树
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    BiTree root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    root->right->right = create_node(6);

    printf("层序遍历结果：");
    level_order(root);
    printf("\n");
    // 预期输出：1 2 3 4 5 6

    return 0;
}
