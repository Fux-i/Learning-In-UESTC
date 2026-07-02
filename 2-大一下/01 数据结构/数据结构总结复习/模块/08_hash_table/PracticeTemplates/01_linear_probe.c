/*
 * 题目：线性探测法构建哈希表
 * 来源：真题163
 * 要求：使用线性探测法构建哈希表
 *
 * 函数声明：
 *   void print_hash_array(int arr[], int n);
 *
 * 参数说明：
 *   arr: 待散列的关键字数组
 *   n: 数组长度（保证为 13）
 *
 * 哈希函数：H(key) = key % 13
 * 冲突处理：线性探测法
 *
 * 示例：
 *   输入：[1, 5, 21, 26, 39, 14, 15, 16, 17, 18, 19, 20, 111]
 *   输出：[26, 1, 39, 14, 15, 5, 16, 17, 21, 18, 19, 20, 111]
 *
 * TODO: 补全 print_hash_array 函数
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 13

// TODO: 补全线性探测法
// 要求：
// 1. 创建大小为 13 的哈希表
// 2. 使用 H(key) = key % 13 作为哈希函数
// 3. 冲突时使用线性探测法
// 4. 打印哈希表内容
void print_hash_array(int arr[], int n) {
    // TODO: 在此补全代码

}

int main() {
    int arr[] = {1, 5, 21, 26, 39, 14, 15, 16, 17, 18, 19, 20, 111};
    int n = 13;

    printf("输入序列：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("哈希表内容：");
    print_hash_array(arr, n);
    printf("\n");
    // 预期输出：26 1 39 14 15 5 16 17 21 18 19 20 111

    return 0;
}
