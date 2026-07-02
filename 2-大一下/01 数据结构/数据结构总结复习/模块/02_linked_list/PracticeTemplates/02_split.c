/*
 * 题目：链表分割
 * 来源：24级三批
 * 要求：将链表按位置分割成两个链表
 *
 * 函数声明：
 *   void split(list *L, int pos, list *L1, list *L2);
 *
 * 参数说明：
 *   L: 指向原链表的指针
 *   pos: 分割位置（L1 包含前 pos 个结点）
 *   L1, L2: 指向结果链表的指针
 *
 * 注意：L2 需要带一个头结点
 *
 * TODO: 补全 split 函数
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node *next;
} node;

typedef struct {
    node *head;
    unsigned len;
} list;

void init_list(list *L) {
    L->head = NULL;
    L->len = 0;
}

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

void print_list(list *L) {
    node *p = L->head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// TODO: 补全分割操作
// 将 L 分割成 L1 和 L2
// L1 包含前 pos 个结点，L2 包含剩余结点
// 注意：L2 需要带一个头结点
void split(list *L, int pos, list *L1, list *L2) {
    // TODO: 在此补全代码

}

int main() {
    list L, L1, L2;
    init_list(&L);
    init_list(&L1);
    init_list(&L2);

    // 构造测试数据
    insert_tail(&L, 10);
    insert_tail(&L, 20);
    insert_tail(&L, 30);
    insert_tail(&L, 40);
    insert_tail(&L, 50);

    printf("原链表 L：");
    print_list(&L);

    split(&L, 3, &L1, &L2);
    printf("L1 (前 3 个)：");
    print_list(&L1);  // 预期输出：10 -> 20 -> 30 -> NULL
    printf("L2 (剩余)：");
    print_list(&L2);  // 预期输出：40 -> 50 -> NULL

    return 0;
}
