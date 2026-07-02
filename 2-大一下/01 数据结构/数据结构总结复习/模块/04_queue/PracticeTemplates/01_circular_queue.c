/*
 * 题目：循环队列基本操作
 * 来源：原 Todo
 * 要求：实现循环队列的基本操作
 *
 * 函数声明：
 *   void init_queue(SqQueue *Q);
 *   bool enter_queue(SqQueue *Q, int x);
 *   bool leave_queue(SqQueue *Q, int *x);
 *   bool is_empty(SqQueue *Q);
 *
 * TODO: 补全四个函数
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 10

typedef struct {
    int elem[MAXSIZE];
    int front;  // 队头指针
    int rear;   // 队尾指针
} SqQueue;

// TODO: 补全初始化操作
void init_queue(SqQueue *Q) {
    // TODO: 在此补全代码

}

// TODO: 补全判空操作
bool is_empty(SqQueue *Q) {
    // TODO: 在此补全代码

}

// TODO: 补全判满操作
// 提示：牺牲一个空间
bool is_full(SqQueue *Q) {
    // TODO: 在此补全代码

}

// TODO: 补全入队操作
// 注意：需要检查队满，更新 rear
bool enter_queue(SqQueue *Q, int x) {
    // TODO: 在此补全代码

}

// TODO: 补全出队操作
// 注意：需要检查队空，更新 front
bool leave_queue(SqQueue *Q, int *x) {
    // TODO: 在此补全代码

}

// 打印队列
void print_queue(SqQueue *Q) {
    if (is_empty(Q)) {
        printf("空队列\n");
        return;
    }
    int i = Q->front;
    while (i != Q->rear) {
        printf("%d ", Q->elem[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
}

int main() {
    SqQueue Q;
    int x;

    // 初始化
    init_queue(&Q);
    printf("队列是否为空：%s\n", is_empty(&Q) ? "是" : "否");  // 预期：是

    // 入队测试
    enter_queue(&Q, 10);
    enter_queue(&Q, 20);
    enter_queue(&Q, 30);
    printf("入队 10, 20, 30 后：");
    print_queue(&Q);  // 预期输出：10 20 30

    // 出队测试
    leave_queue(&Q, &x);
    printf("出队元素：%d\n", x);  // 预期：10
    printf("出队后：");
    print_queue(&Q);  // 预期输出：20 30

    // 测试循环特性
    enter_queue(&Q, 40);
    enter_queue(&Q, 50);
    printf("入队 40, 50 后：");
    print_queue(&Q);  // 预期输出：20 30 40 50

    return 0;
}
