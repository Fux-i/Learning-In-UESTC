/*
 * 题目：关键路径计算
 * 来源：23级、24级、真题161
 * 要求：计算 AOE 网的关键路径
 *
 * 函数声明：
 *   int check_key_path(int* path);
 *
 * 参数说明：
 *   path: 用于保存关键路径顶点编号的数组
 *
 * 返回值：
 *   关键路径的长度
 *
 * 说明：
 *   - 图有 6 个顶点（0~5）
 *   - 邻接矩阵已给出
 *   - 需要计算最早发生时间 etv 和最迟发生时间 ltv
 *
 * TODO: 补全关键路径计算
 */

#include <stdio.h>

#define MAX_VERTEX_NUM 6
#define INF 99999

// 测试用邻接矩阵
int a[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {
    {INF, 4,  6,  INF, INF, INF},
    {INF, INF, 5,  INF, INF, INF},
    {INF, INF, INF, 4,  3,  INF},
    {INF, INF, INF, INF, INF, 3},
    {INF, INF, INF, INF, INF, 3},
    {INF, INF, INF, INF, INF, INF}
};

// TODO: 补全关键路径计算
// 要求：
// 1. 计算 etv（最早发生时间）
// 2. 计算 ltv（最迟发生时间）
// 3. 找出关键路径
// 4. 将关键路径顶点保存到 path 数组
// 5. 返回关键路径长度
int check_key_path(int* path) {
    // TODO: 在此补全代码

}

int main() {
    int path[MAX_VERTEX_NUM];
    int len = check_key_path(path);

    printf("关键路径长度：%d\n", len);
    printf("关键路径顶点：");
    for (int i = 0; i < len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return 0;
}
