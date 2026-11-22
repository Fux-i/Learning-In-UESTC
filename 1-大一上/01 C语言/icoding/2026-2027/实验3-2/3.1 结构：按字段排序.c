#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // 定义键值对类型
    char key[10];
    int value;
} kv_pair;

#define MAXN 30

// 定义用于比较的回调函数类型
typedef int cmp_fn(const kv_pair *, const kv_pair *);

int cmp_key(const kv_pair *a, const kv_pair *b);
int cmp_value(const kv_pair *a, const kv_pair *b);
void bubble_sort(kv_pair *dict, int n, cmp_fn cmp);

kv_pair dict[MAXN];

int main() {
    int n;
    scanf("%d", &n); // 测试用例保证0 < n <= 30
    for (int i = 0; i < n; ++i) {
        scanf("%s %d", dict[i].key, &dict[i].value);
    }

    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        bubble_sort(dict, n, cmp_key);
    } else {
        bubble_sort(dict, n, cmp_value);
    }

    for (int i = 0; i < n; ++i) {
        printf("{%s,%d}", dict[i].key, dict[i].value);
    }
    printf("\n");
    return 0;
}

// 请勿删除或修改此行以上的所有内容！！！
// 你的代码写在TODO和END OF TODO之间

// 用于键的三向比较函数：a->key大于b->key 返回正值，相等返回0，小于返回负值
int cmp_key(const kv_pair *a, const kv_pair *b) {
    return strcmp(a->key, b->key);
    // END OF TODO
}

// 用于值的比较函数：a->value大于b->value 返回正值，相等返回0，小于返回负值
int cmp_value(const kv_pair *a, const kv_pair *b) {
    if (a->value > b->value)
        return 1;
    if (a->value < b->value)
        return -1;
    return 0;
    // END OF TODO
}

// 冒泡排序。dict：待排序的数组；n：数组的长度；cmp：比较函数
void bubble_sort(kv_pair *dict, int n, cmp_fn cmp) {
    int i, j;
    kv_pair tmp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (cmp(&dict[j], &dict[j + 1]) > 0) {
                tmp = dict[j];
                dict[j] = dict[j + 1];
                dict[j + 1] = tmp;
            }
        }
    }
    // END OF TODO
}
