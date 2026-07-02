/*
 * 题目：计算图的入度和出度
 * 来源：23级三轮、24级三批、24级二批
 * 要求：计算邻接矩阵中指定顶点的入度和出度
 *
 * 函数声明：
 *   int indegree(MatrixGraph *G, int v);
 *   int outdegree(MatrixGraph *G, int v);
 *
 * 参数说明：
 *   G: 指向图的指针
 *   v: 顶点下标（从0开始）
 *
 * 返回值：
 *   入度/出度值
 *
 * TODO: 补全两个函数
 */

#include <stdio.h>

#define MAX_VERTEX_NUM 20

typedef struct {
    int vertex[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum;
} MatrixGraph;

// TODO: 补全入度计算
// 入度：有多少条边指向顶点 v
// 提示：遍历第 v 列
int indegree(MatrixGraph *G, int v) {
    // TODO: 在此补全代码

}

// TODO: 补全出度计算
// 出度：从顶点 v 出发有多少条边
// 提示：遍历第 v 行
int outdegree(MatrixGraph *G, int v) {
    // TODO: 在此补全代码

}

int main() {
    MatrixGraph G = {0};
    G.vexnum = 4;

    // 构造测试图
    // 0 -> 1, 0 -> 2
    // 1 -> 3
    // 2 -> 3
    G.arcs[0][1] = 1;
    G.arcs[0][2] = 1;
    G.arcs[1][3] = 1;
    G.arcs[2][3] = 1;

    printf("图的邻接矩阵：\n");
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            printf("%d ", G.arcs[i][j]);
        }
        printf("\n");
    }

    // 测试入度和出度
    for (int i = 0; i < G.vexnum; i++) {
        printf("顶点 %d: 入度=%d, 出度=%d\n", i, indegree(&G, i), outdegree(&G, i));
    }
    // 预期输出：
    // 顶点 0: 入度=0, 出度=2
    // 顶点 1: 入度=1, 出度=1
    // 顶点 2: 入度=1, 出度=1
    // 顶点 3: 入度=2, 出度=0

    return 0;
}
