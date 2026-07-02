/*
 * 题目：删除顺序表中满足条件的元素
 * 来源：真题176、真题197
 * 要求：删除顺序表中所有能被指定整数整除的元素（或保留偶数）
 *
 * 函数声明：
 *   void remove_elem(SeqList *L, int f);
 *
 * 参数说明：
 *   L: 指向顺序表的指针
 *   f: 整除因子（f >= 2）
 *
 * 要求：原地操作，时间复杂度 O(n)，空间复杂度 O(1)
 *
 * TODO: 补全 remove_elem 函数
 */

#include <stdio.h>

#define MAXLEN 128

typedef struct {
    int elem[MAXLEN];
    int len;
} list;

void printList(list *L) {
    for (int i = 0; i < L->len; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

// TODO: 补全删除操作
// 删除所有能被 f 整除的元素
// 要求：1. 双指针法 2. 时间复杂度 O(n) 3. 更新 len
void remove_elem(list *L, int f) {
    // TODO: 在此补全代码

}

int main() {
    list L;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15};
    L.len = 12;
    for (int i = 0; i < L.len; i++) {
        L.elem[i] = data[i];
    }

    printf("原表：");
    printList(&L);

    remove_elem(&L, 3);
    printf("删除能被 3 整除的元素后：");
    printList(&L);
    // 预期输出：1 2 4 5 7 8 10

    return 0;
}
