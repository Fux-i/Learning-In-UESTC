/*
 * 题目：顺序表段交换
 * 来源：24级一批
 * 要求：将顺序表的 [0, pos-1] 和 [pos, n-1] 两段交换
 *
 * 函数声明：
 *   void swap(SeqList *L, int pos);
 *
 * 参数说明：
 *   L: 指向顺序表的指针
 *   pos: 分割位置
 *
 * 示例：
 *   原表：[1, 2, 3, 4, 5, 6]，pos = 3
 *   结果：[4, 5, 6, 1, 2, 3]
 *
 * TODO: 补全 swap 函数
 */

#include <stdio.h>

#define MAXSIZE 100

typedef struct {
    int elem[MAXSIZE];
    int last;
} SeqList;

void printList(SeqList *L) {
    for (int i = 0; i <= L->last; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

// TODO: 补全段交换操作
// 将 [0, pos-1] 和 [pos, last] 交换
// 提示：可以使用辅助数组
void swap(SeqList *L, int pos) {
    // TODO: 在此补全代码

}

int main() {
    SeqList L;
    int data[] = {1, 2, 3, 4, 5, 6};
    L.last = 5;
    for (int i = 0; i <= L.last; i++) {
        L.elem[i] = data[i];
    }

    printf("原表：");
    printList(&L);

    swap(&L, 3);
    printf("交换后（pos=3）：");
    printList(&L);
    // 预期输出：4 5 6 1 2 3

    return 0;
}
