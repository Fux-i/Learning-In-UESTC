/*
 * 题目：判断有向图中是否存在欧拉通路
 * 来源：真题200
 * 要求：判断邻接矩阵表示的有向图中是否存在欧拉通路
 *
 * 欧拉通路条件（有向图）：
 *   1. 所有顶点的入度和出度之差的绝对值不超过 1
 *   2. 入度比出度大 1 的顶点个数为 0 或 1
 *   3. 出度比入度大 1 的顶点个数为 0 或 1
 *
 * 函数声明：
 *   bool if_eulerpath(MatrixGraph *G);
 *
 * 参数说明：
 *   G: 指向邻接矩阵表示的有向图的指针
 *
 * 返回值：
 *   存在欧拉通路返回 true，否则返回 false
 *
 * TODO: 补全 if_eulerpath 函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20

typedef struct {
    int vertex[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum;
} MatrixGraph;

// TODO: 补全欧拉通路判断
// 要求：
// 1. 计算每个顶点的入度和出度
// 2. 判断是否满足欧拉通路条件
bool if_eulerpath(MatrixGraph *G) {
    // TODO: 在此补全代码

}

int main() {
    // 测试用例 1：存在欧拉通路
    MatrixGraph G1 = {0};
    G1.vexnum = 4;
    G1.arcs[0][1] = 1;  // 0->1
    G1.arcs[1][2] = 1;  // 1->2
    G1.arcs[2][3] = 1;  // 2->3

    printf("图1是否存在欧拉通路：%s\n", if_eulerpath(&G1) ? "是" : "否");
    // 预期：是（0出度1，1入度1出度1，2入度1出度1，3入度1）

    // 测试用例 2：不存在欧拉通路
    MatrixGraph G2 = {0};
    G2.vexnum = 3;
    G2.arcs[0][1] = 1;  // 0->1
    G2.arcs[0][2] = 1;  // 0->2
    G2.arcs[1][2] = 1;  // 1->2

    printf("图2是否存在欧拉通路：%s\n", if_eulerpath(&G2) ? "是" : "否");
    // 预期：否（0出度2，1入度1出度1，2入度2）

    return 0;
}
