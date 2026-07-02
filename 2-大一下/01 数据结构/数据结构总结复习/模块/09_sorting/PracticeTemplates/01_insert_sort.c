/*
 * 题目：直接插入排序
 * 来源：23级三轮
 * 要求：实现直接插入排序算法
 *
 * 函数声明：
 *   void insert_sort(int arr[], int n);
 *
 * 参数说明：
 *   arr: 待排序数组
 *   n: 数组长度
 *
 * 关键逻辑：
 *   1. 从第 2 个元素开始（i=1）
 *   2. 从后往前找插入位置
 *   3. 元素后移腾出空间
 *
 * TODO: 补全 insert_sort 函数
 */

#include <stdio.h>

// TODO: 补全直接插入排序
// 要求：
// 1. 从 i=1 开始遍历
// 2. 保存当前元素 temp
// 3. 从后往前找插入位置，元素后移
// 4. 插入 temp 到正确位置
void insert_sort(int arr[], int n) {
    // TODO: 在此补全代码

}

// 打印数组
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // 测试用例 1
    int arr1[] = {5, 3, 1, 4, 2};
    int n1 = 5;
    printf("排序前：");
    print_array(arr1, n1);
    insert_sort(arr1, n1);
    printf("排序后：");
    print_array(arr1, n1);
    // 预期输出：1 2 3 4 5

    // 测试用例 2：已有序
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;
    printf("排序前：");
    print_array(arr2, n2);
    insert_sort(arr2, n2);
    printf("排序后：");
    print_array(arr2, n2);
    // 预期输出：1 2 3 4 5

    // 测试用例 3：逆序
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = 5;
    printf("排序前：");
    print_array(arr3, n3);
    insert_sort(arr3, n3);
    printf("排序后：");
    print_array(arr3, n3);
    // 预期输出：1 2 3 4 5

    return 0;
}
