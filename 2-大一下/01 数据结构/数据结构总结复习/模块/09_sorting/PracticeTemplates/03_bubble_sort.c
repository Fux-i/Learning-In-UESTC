/*
 * 题目：冒泡排序
 * 来源：原 Todo
 * 要求：实现冒泡排序算法
 *
 * 函数声明：
 *   void bubble_sort(int arr[], int n);
 *
 * 参数说明：
 *   arr: 待排序数组
 *   n: 数组长度
 *
 * 关键逻辑：
 *   1. 每轮将最大值冒泡到最后
 *   2. 相邻元素比较交换
 *   3. 如果某轮没有交换，提前结束
 *
 * TODO: 补全 bubble_sort 函数
 */

#include <stdio.h>

// TODO: 补全冒泡排序
// 要求：
// 1. 外层循环 i 从 0 到 n-2
// 2. 内层循环 j 从 0 到 n-2-i
// 3. 相邻元素比较，如果 arr[j] > arr[j+1] 则交换
// 4. 如果某轮没有交换，提前结束
void bubble_sort(int arr[], int n) {
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
    bubble_sort(arr1, n1);
    printf("排序后：");
    print_array(arr1, n1);
    // 预期输出：1 2 3 4 5

    // 测试用例 2：已有序
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = 5;
    printf("排序前：");
    print_array(arr2, n2);
    bubble_sort(arr2, n2);
    printf("排序后：");
    print_array(arr2, n2);
    // 预期输出：1 2 3 4 5

    // 测试用例 3：逆序
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = 5;
    printf("排序前：");
    print_array(arr3, n3);
    bubble_sort(arr3, n3);
    printf("排序后：");
    print_array(arr3, n3);
    // 预期输出：1 2 3 4 5

    return 0;
}
