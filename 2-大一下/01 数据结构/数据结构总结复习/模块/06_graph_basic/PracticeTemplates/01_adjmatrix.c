/*
 * 题目：邻接矩阵基本操作
 * 来源：真题127
 * 要求：实现邻接矩阵的插入顶点和插入边操作
 *
 * 函数声明：
 *   bool matrix_insert_vertex(MatrixGraph *G, VertexType v);
 *   bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w);
 *
 * 参数说明：
 *   G: 指向图的指针
 *   v, w: 顶点
 *
 * 返回值：
 *   成功返回 true，失败返回 false
 *
 * TODO: 补全两个函数
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20

typedef int VertexType;

typedef enum {
    DG,   // 有向图
    UDG   // 无向图
} GraphType;

typedef struct {
    VertexType vertex[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
} MatrixGraph;

// 定位顶点在数组中的下标
int matrix_locate_vertex(MatrixGraph *G, VertexType v) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertex[i] == v) return i;
    }
    return -1;
}

// TODO: 补全插入顶点操作
// 要求：1. 检查是否已满 2. 检查是否已存在
bool matrix_insert_vertex(MatrixGraph *G, VertexType v) {
    // TODO: 在此补全代码

}

// TODO: 补全插入边操作
// 要求：1. 定位顶点 2. 检查边是否已存在 3. 无向图双向设置
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w) {
    // TODO: 在此补全代码

}

// 打印邻接矩阵
void print_graph(MatrixGraph *G) {
    printf("顶点：");
    for (int i = 0; i < G->vexnum; i++) {
        printf("%d ", G->vertex[i]);
    }
    printf("\n邻接矩阵：\n");
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            printf("%d ", G->arcs[i][j]);
        }
        printf("\n");
    }
}

int main() {
    MatrixGraph G = {0};
    G.type = DG;  // 有向图

    // 插入顶点
    matrix_insert_vertex(&G, 1);
    matrix_insert_vertex(&G, 2);
    matrix_insert_vertex(&G, 3);
    matrix_insert_vertex(&G, 4);

    // 插入边
    matrix_insert_arc(&G, 1, 2);
    matrix_insert_arc(&G, 1, 3);
    matrix_insert_arc(&G, 2, 4);
    matrix_insert_arc(&G, 3, 4);

    print_graph(&G);
    // 预期输出：
    // 顶点：1 2 3 4
    // 邻接矩阵：
    // 0 1 1 0
    // 0 0 0 1
    // 0 0 0 1
    // 0 0 0 0

    return 0;
}
