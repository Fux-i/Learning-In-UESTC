/*
 * 题目：哈希排序
 * 来源：真题182
 * 要求：利用无重复值特性进行排序
 *
 * 函数声明：
 *   void xsort(unsigned *a, unsigned n);
 *
 * 参数说明：
 *   a: 待排序数组
 *   n: 数组长度
 *
 * 特点：
 *   - 元素在 1~m 之间
 *   - n < m
 *   - 元素没有重复值
 *   - 时间复杂度要求 O(m)
 *
 * 提示：利用 hash(K) = K，将数据散列到长度为 m 的数组中
 *
 * TODO: 补全 xsort 函数
 */

#include <stdio.h>
#include <stdlib.h>

// TODO: 补全哈希排序
// 要求：
// 1. 找到数组中的最大值 m
// 2. 创建大小为 m+1 的计数数组
// 3. 将元素散列到计数数组
// 4. 收集回原数组
void xsort(unsigned *a, unsigned n) {
    // TODO: 在此补全代码

}

// 打印数组
void print_array(unsigned *a, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        printf("%u ", a[i]);
    }
    printf("\n");
}

int main() {
    // 测试用例 1
    unsigned a1[] = {5, 3, 1, 4, 2};
    unsigned n1 = 5;
    printf("排序前：");
    print_array(a1, n1);
    xsort(a1, n1);
    printf("排序后：");
    print_array(a1, n1);
    // 预期输出：1 2 3 4 5

    // 测试用例 2
    unsigned a2[] = {10, 7, 3, 8, 1, 9, 2, 6, 4, 5};
    unsigned n2 = 10;
    printf("排序前：");
    print_array(a2, n2);
    xsort(a2, n2);
    printf("排序后：");
    print_array(a2, n2);
    // 预期输出：1 2 3 4 5 6 7 8 9 10

    // 测试用例 3：空数组
    unsigned a3[] = {};
    unsigned n3 = 0;
    printf("空数组排序：");
    xsort(a3, n3);
    print_array(a3, n3);
    // 预期输出：（空）

    return 0;
}
