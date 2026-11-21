#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 128
int arr[MAX_SIZE + 1];

// 检查数组 arr[1..n] 是否为第一趟希尔排序（gap = n/2）后的结果。
bool is_first_shellsort(int arr[], int n);

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &arr[i]);

    printf(is_first_shellsort(arr, n) ? "Yes\n" : "No\n");

    return 0;
}

// --- 测试代码结束 ---------------------------------------------------------

// 你的代码写在 TODO和END OF TODO之间。
// 请勿将你的代码写在这对标签之外！！！
// 请勿修改这对标签外的任何代码！！！

/**
 * @brief 检查数组 arr[1..n] 是否为第一趟希尔排序（gap = n/2）后的结果。
 *
 * @param arr 数组。下标从1开始
 * @param n 元素个数
 * @return bool 如果是返回true，否则返回false
 */
bool is_first_shellsort(int arr[], int n) {
    if (n <= 1)
        return true;

    int gap = n / 2;
    for (int i = 1; i <= gap; i++) {
        for (int j = i + gap; j <= n; j += gap) {
            if (arr[j - gap] > arr[j])
                return false;
        }
    }
    return true;
    // END OF TODO
}
