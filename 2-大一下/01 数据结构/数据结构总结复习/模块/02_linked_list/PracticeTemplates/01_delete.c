/*
 * 题目：链表删除操作
 * 来源：23级三轮
 * 要求：删除链表中第一个值为 x 的结点
 *
 * 函数声明：
 *   bool delete_by_value(list *L, int x);
 *
 * 参数说明：
 *   L: 指向链表的指针
 *   x: 要删除的元素值
 *
 * 返回值：
 *   删除成功返回 true，未找到返回 false
 *
 * TODO: 补全 delete_by_value 函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node {
    int data;
    struct _node *next;
} node;

typedef struct {
    node *head;
    unsigned len;
} list;

// 初始化链表
void init_list(list *L) {
    L->head = NULL;
    L->len = 0;
}

// 尾插法建表
void insert_tail(list *L, int x) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = x;
    newNode->next = NULL;

    if (L->head == NULL) {
        L->head = newNode;
    } else {
        node *p = L->head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }
    L->len++;
}

// 打印链表
void print_list(list *L) {
    node *p = L->head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// TODO: 补全删除操作
// 删除第一个值为 x 的结点
// 要求：1. 处理空链表 2. 找到前驱 3. 释放内存
bool delete_by_value(list *L, int x) {
    // TODO: 在此补全代码

}

int main() {
    list L;
    init_list(&L);

    // 构造测试数据
    insert_tail(&L, 10);
    insert_tail(&L, 20);
    insert_tail(&L, 30);
    insert_tail(&L, 40);
    insert_tail(&L, 50);

    printf("原链表：");
    print_list(&L);

    // 测试删除中间结点
    delete_by_value(&L, 30);
    printf("删除 30 后：");
    print_list(&L);  // 预期输出：10 -> 20 -> 40 -> 50 -> NULL

    // 测试删除头结点
    delete_by_value(&L, 10);
    printf("删除 10 后：");
    print_list(&L);  // 预期输出：20 -> 40 -> 50 -> NULL

    // 测试删除不存在的结点
    bool result = delete_by_value(&L, 99);
    printf("删除 99 结果：%s\n", result ? "成功" : "失败");

    return 0;
}
