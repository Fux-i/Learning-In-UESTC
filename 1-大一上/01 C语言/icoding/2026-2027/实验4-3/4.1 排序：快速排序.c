#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 128
int arr[MAX_SIZE + 1];

// 验证数组 arr[1..n] 是否是第一趟快速排序的结果
bool is_first_quicksort(int arr[], int n, int pivot);

int main() {
    int n, pivot;
    scanf("%d%d", &n, &pivot);
    for (int i = 1; i <= MAX_SIZE; ++i)
        arr[i] = -1;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &arr[i]);

    printf(is_first_quicksort(arr, n, pivot) ? "Yes\n" : "No\n");

    return 0;
}

// --- 测试代码结束 ---------------------------------------------------------

// 你的代码写在 TODO和END OF TODO之间。
// 请勿将你的代码写在这对标签之外！！！
// 请勿修改这对标签外的任何代码！！！

/**
 * @brief 验证数组 arr[1..n] 是否是第一趟快速排序的结果
 *
 * @param arr 数组，下标从1开始
 * @param n 元素个数
 * @param pivot 枢轴元素下标
 * @return bool 如果是返回true，否则返回false
 */
bool is_first_quicksort(int arr[], int n, int pivot) {
    if (n <= 1)
        return true;

    int p = arr[pivot];
    for (int i = 1; i < pivot; i++) {
        if (arr[i] > p)
            return false;
    }
    for (int i = pivot + 1; i <= n; i++) {
        if (arr[i] < p)
            return false;
    }
    return true;
    // ENDOFTODO
}
