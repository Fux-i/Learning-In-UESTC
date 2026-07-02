/*
 * 题目：合并两个有序顺序表
 * 来源：23级期末、真题160、真题201
 * 要求：将两个非递减有序顺序表合并为一个非递减有序顺序表
 *
 * 函数声明：
 *   void merge(SeqList *LA, SeqList *LB, SeqList *LC);
 *
 * 参数说明：
 *   LA, LB: 指向两个有序顺序表的指针
 *   LC: 指向结果顺序表的指针
 *
 * TODO: 补全 merge 函数
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

// TODO: 补全合并操作
// 将 LA 和 LB 合并到 LC 中，保持非递减顺序
// 要求：1. 双指针比较 2. 处理剩余元素 3. 更新 last
void merge(SeqList *LA, SeqList *LB, SeqList *LC) {
    // TODO: 在此补全代码

}

int main() {
    SeqList LA, LB, LC;
    initList(&LA);
    initList(&LB);
    initList(&LC);

    // 构造测试数据
    LA.elem[0] = 1; LA.elem[1] = 3; LA.elem[2] = 5; LA.elem[3] = 7;
    LA.last = 3;

    LB.elem[0] = 2; LB.elem[1] = 4; LB.elem[2] = 6; LB.elem[3] = 8; LB.elem[4] = 10;
    LB.last = 4;

    printf("LA: ");
    printList(&LA);
    printf("LB: ");
    printList(&LB);

    merge(&LA, &LB, &LC);
    printf("LC (合并后): ");
    printList(&LC);
    // 预期输出：1 2 3 4 5 6 7 8 10

    return 0;
}
