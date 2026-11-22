#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 128
int arr[MAX_SIZE + 1];

// 验证数组 arr[1..n] 是否是第一趟二路归并排序的结果
bool is_first_mergesort(int arr[], int n);

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= MAX_SIZE; ++i)
        arr[i] = -1;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &arr[i]);

    printf(is_first_mergesort(arr, n) ? "Yes\n" : "No\n");

    return 0;
}

/**
 * @brief 验证数组 arr[1..n] 是否是第一趟二路归并排序的结果
 *
 * @param arr 数组。下标从1开始
 * @param n 元素个数
 * @return bool 如果是返回true，否则返回false
 */
bool is_first_mergesort(int arr[], int n) {
    if (n <= 1)
        return true;

    for (int i = 1; i + 1 <= n; i += 2) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
    // END OF TODO
}
