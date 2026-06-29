/*
 * 题目：链址法构建哈希表
 * 来源：真题199
 * 要求：使用链址法构建哈希表
 *
 * 函数声明：
 *   void hashing(hashnode *ht[], int *keys, int n);
 *
 * 参数说明：
 *   ht: 哈希表（指针数组，每个元素是链表头指针）
 *   keys: 待散列的关键字数组
 *   n: keys 数组的长度
 *
 * 说明：
 *   - 哈希表长度 P 为全局变量
 *   - 冲突时使用头插法
 *
 * TODO: 补全 hashing 函数
 */

#include <stdio.h>
#include <stdlib.h>

#define P 7  // 哈希表长度

typedef struct hashnode {
    int key;
    struct hashnode *next;
} hashnode;

// TODO: 补全链址法
// 要求：
// 1. 计算哈希值：key % P
// 2. 创建新结点
// 3. 使用头插法插入链表
void hashing(hashnode *ht[], int *keys, int n) {
    // TODO: 在此补全代码

}

// 打印哈希表
void print_hash_table(hashnode *ht[]) {
    for (int i = 0; i < P; i++) {
        printf("[%d]: ", i);
        hashnode *p = ht[i];
        while (p != NULL) {
            printf("%d -> ", p->key);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int main() {
    hashnode *ht[P] = {NULL};
    int keys[] = {7, 14, 1, 9, 16, 10, 11};
    int n = 7;

    printf("输入序列：");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
    }
    printf("\n\n");
    
    hashing(ht, keys, n);

    printf("哈希表内容：\n");
    print_hash_table(ht);
    // 预期输出（头插法，顺序相反）：
    // [0]: 14 -> 7 -> NULL
    // [1]: 1 -> NULL
    // [2]: 16 -> 9 -> NULL
    // [3]: 10 -> NULL
    // [4]: 11 -> NULL
    // [5]: NULL
    // [6]: NULL

    return 0;
}
