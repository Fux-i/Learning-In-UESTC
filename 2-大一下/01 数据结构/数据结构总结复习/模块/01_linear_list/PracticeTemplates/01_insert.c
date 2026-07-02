/*
 * 题目：顺序表插入操作
 * 来源：23级期末、真题160
 * 要求：在顺序表的指定位置插入元素
 *
 * 函数声明：
 *   bool insert(SeqList *L, int pos, int x);
 *
 * 参数说明：
 *   L: 指向顺序表的指针
 *   pos: 插入位置（从0开始）
 *   x: 要插入的元素
 *
 * 返回值：
 *   插入成功返回 true，失败返回 false
 *
 * TODO: 补全 insert 函数
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct {
    int elem[MAXSIZE];
    int last;  // 最后一个元素的下标，空表时为 -1
} SeqList;

// 初始化顺序表
void initList(SeqList *L) {
    L->last = -1;
}

// 打印顺序表
void printList(SeqList *L) {
    for (int i = 0; i <= L->last; i++) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

// TODO: 补全插入操作
// 在位置 pos 插入元素 x
// 要求：1. 检查表满 2. 检查位置合法性 3. 移动元素 4. 更新 last
bool insert(SeqList *L, int pos, int x) {
    // TODO: 在此补全代码

}

int main() {
    SeqList L;
    initList(&L);

    // 测试用例 1：正常插入
    insert(&L, 0, 10);
    insert(&L, 1, 20);
    insert(&L, 2, 30);
    printf("插入 10, 2, 30 后：");
    printList(&L);  // 预期输出：10 20 30

    // 测试用例 2：中间插入
    insert(&L, 1, 15);
    printf("在位置 1 插入 15 后：");
    printList(&L);  // 预期输出：10 15 20 30

    // 测试用例 3：头部插入
    insert(&L, 0, 5);
    printf("在位置 0 插入 5 后：");
    printList(&L);  // 预期输出：5 10 15 20 30

    // 测试用例 4：非法位置
    bool result = insert(&L, 10, 99);
    printf("在位置 10 插入 99 结果：%s\n", result ? "成功" : "失败");

    return 0;
}
