/*
 * 题目：顺序表按位置分割
 * 来源：24级一批、24级二批
 * 要求：将顺序表按指定位置分割成两个顺序表
 *
 * 函数声明：
 *   void split(SeqList *L, int pos, SeqList *L1, SeqList *L2);
 *
 * 参数说明：
 *   L: 指向原顺序表的指针
 *   pos: 分割位置（L1 包含 [0, pos-1]，L2 包含 [pos, last]）
 *   L1, L2: 指向结果顺序表的指针
 *
 * TODO: 补全 split 函数
 */

#include <stdio.h>

#define MAXSIZE 100

typedef struct {
    int elem[MAXSIZE];
    int last;
} SeqList;

void initList(SeqList *L) {
    L->last = -1;
}

void printList(SeqList *L) {
    for (int i = 0; i <= L->last; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

// TODO: 补全分割操作
// 将 L 分割成 L1 和 L2
// L1 包含 [0, pos-1]，L2 包含 [pos, last]
void split(SeqList *L, int pos, SeqList *L1, SeqList *L2) {
    // TODO: 在此补全代码

}

int main() {
    SeqList L, L1, L2;
    initList(&L);
    initList(&L1);
    initList(&L2);

    // 构造测试数据
    int data[] = {10, 20, 30, 40, 50, 60};
    L.last = 5;
    for (int i = 0; i <= L.last; i++) {
        L.elem[i] = data[i];
    }

    printf("原表 L：");
    printList(&L);

    split(&L, 3, &L1, &L2);
    printf("L1 (前半部分)：");
    printList(&L1);  // 预期输出：10 20 30
    printf("L2 (后半部分)：");
    printList(&L2);  // 预期输出：40 50 60

    return 0;
}
