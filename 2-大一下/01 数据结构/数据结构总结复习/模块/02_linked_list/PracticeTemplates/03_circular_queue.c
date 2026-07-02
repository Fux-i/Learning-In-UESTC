/*
 * 题目：循环链表表示队列
 * 来源：真题113
 * 要求：用循环链表实现队列的基本操作
 *
 * 函数声明：
 *   bool init_queue(LinkQueue *LQ);
 *   bool enter_queue(LinkQueue *LQ, int x);
 *   bool leave_queue(LinkQueue *LQ, int *x);
 *
 * 说明：
 *   - 带头结点的循环链表
 *   - 只设一个指针指向队尾元素结点
 *   - 不设头指针
 *
 * TODO: 补全三个函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _QueueNode {
    int data;
    struct _QueueNode *next;
} LinkQueueNode, *LinkQueue;

// TODO: 补全初始化操作
// 创建头结点，形成循环
bool init_queue(LinkQueue *LQ) {
    // TODO: 在此补全代码

}

// TODO: 补全入队操作
// 新结点插入到队尾
// 提示：需要找到队尾（最后一个结点）
bool enter_queue(LinkQueue *LQ, int x) {
    // TODO: 在此补全代码

}

// TODO: 补全出队操作
// 删除队首元素（头结点的下一个结点）
bool leave_queue(LinkQueue *LQ, int *x) {
    // TODO: 在此补全代码

}

// 打印队列
void print_queue(LinkQueue LQ) {
    if (LQ->next == LQ) {
        printf("空队列\n");
        return;
    }
    LinkQueueNode *p = LQ->next;
    while (p != LQ) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    LinkQueue LQ;
    int x;

    // 初始化
    init_queue(&LQ);
    printf("初始化后：");
    print_queue(LQ);

    // 入队测试
    enter_queue(&LQ, 10);
    enter_queue(&LQ, 20);
    enter_queue(&LQ, 30);
    printf("入队 10, 20, 30 后：");
    print_queue(LQ);  // 预期输出：10 20 30

    // 出队测试
    leave_queue(&LQ, &x);
    printf("出队元素：%d\n", x);  // 预期输出：10
    printf("出队后：");
    print_queue(LQ);  // 预期输出：20 30

    // 继续测试
    enter_queue(&LQ, 40);
    printf("入队 40 后：");
    print_queue(LQ);  // 预期输出：20 30 40

    return 0;
}
