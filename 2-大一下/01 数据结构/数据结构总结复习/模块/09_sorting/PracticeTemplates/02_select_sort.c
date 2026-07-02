/*
 * 题目：简单选择排序
 * 来源：23级二轮
 * 要求：实现简单选择排序算法
 *
 * 函数声明：
 *   void select_sort(int arr[], int n);
 *
 * 参数说明：
 *   arr: 待排序数组
 *   n: 数组长度
 *
 * 关键逻辑：
 *   1. 每轮找到最小值的位置
 *   2. 将最小值交换到前面
 *   3. 交换次数少
 *
 * TODO: 补全 select_sort 函数
 */

#include <stdio.h>

// TODO: 补全简单选择排序
// 要求：
// 1. 外层循环 i 从 0 到 n-2
// 2. 内层循环找最小值下标 min
// 3. 如果 min != i，交换 arr[i] 和 arr[min]
void select_sort(int arr[], int n) {
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
    select_sort(arr1, n1);
    printf("排序后：");
    print_array(arr1, n1);
    // 预期输出：1 2 3 4 5

    // 测试用例 2：已有序
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;
    printf("排序前：");
    print_array(arr2, n2);
    select_sort(arr2, n2);
    printf("排序后：");
    print_array(arr2, n2);
    // 预期输出：1 2 3 4 5

    // 测试用例 3：逆序
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = 5;
    printf("排序前：");
    print_array(arr3, n3);
    select_sort(arr3, n3);
    printf("排序后：");
    print_array(arr3, n3);
    // 预期输出：1 2 3 4 5

    return 0;
}
