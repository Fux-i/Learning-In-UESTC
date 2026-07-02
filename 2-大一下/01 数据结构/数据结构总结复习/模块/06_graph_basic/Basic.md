# 图的存储与基本操作

## 核心考点

- 邻接矩阵结构定义
- 邻接表结构定义
- 邻接矩阵插入顶点/边
- 计算顶点入度/出度
- 图的焊接（邻接表合并）

---

## 必须会写的代码

1. 邻接矩阵结构定义
2. 邻接表结构定义
3. 邻接矩阵插入操作
4. 计算入度/出度

---

## 典型代码讲解

### 1. 邻接矩阵结构定义

```c
#define MAX_VERTEX_NUM 20

typedef int VertexType;

typedef enum {
    DG,   // 有向图
    UDG   // 无向图
} GraphType;

typedef struct {
    VertexType vertex[MAX_VERTEX_NUM];  // 顶点向量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 邻接矩阵
    int vexnum, arcnum;  // 顶点数和弧数
    GraphType type;  // 图的类型
} MatrixGraph;
```

**要点**：
- `vertex` 数组存储顶点
- `arcs` 二维数组存储边（弧）
- 有向图：`arcs[i][j] = 1` 表示从 i 到 j 有弧
- 无向图：`arcs[i][j] = arcs[j][i] = 1`

### 2. 邻接表结构定义

```c
#define MAX_VERTEX_NUM 20

typedef struct _arc_node {
    int adjvex;  // 该弧指向顶点的序号
    struct _arc_node *nextarc;  // 指向下一条弧
} arc_node;

typedef struct vertex_node {
    char tag;  // 顶点标签
    arc_node *firstarc;  // 指向第一条弧
} vertex_node;

typedef struct {
    vertex_node vertex[MAX_VERTEX_NUM];  // 顶点向量
    int vexnum, arcnum;  // 顶点数和弧数
} adjlist;
```

**要点**：
- 每个顶点有一个链表存储相邻的边
- 节省空间，适合稀疏图

### 3. 邻接矩阵插入顶点

```c
bool matrix_insert_vertex(MatrixGraph *G, VertexType v) {
    // 检查是否已满
    if (G->vexnum >= MAX_VERTEX_NUM) {
        return false;
    }
    // 检查是否已存在
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertex[i] == v) {
            return false;
        }
    }
    // 插入
    G->vertex[G->vexnum++] = v;
    return true;
}
```

### 4. 邻接矩阵插入边

```c
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w) {
    // 定位顶点
    int vIndex = -1, wIndex = -1;
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertex[i] == v) vIndex = i;
        if (G->vertex[i] == w) wIndex = i;
    }
    // 检查顶点是否存在
    if (vIndex < 0 || wIndex < 0) {
        return false;
    }
    // 检查边是否已存在
    if (G->arcs[vIndex][wIndex] != 0) {
        return false;
    }
    // 插入边
    G->arcs[vIndex][wIndex] = 1;
    G->arcnum++;
    // 无向图需要双向设置
    if (G->type == UDG) {
        G->arcs[wIndex][vIndex] = 1;
    }
    return true;
}
```

### 5. 计算入度/出度

```c
// 计算顶点 v 的入度
int indegree(MatrixGraph *G, int v) {
    int count = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (G->arcs[i][v] != 0) {
            count++;
        }
    }
    return count;
}

// 计算顶点 v 的出度
int outdegree(MatrixGraph *G, int v) {
    int count = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (G->arcs[v][i] != 0) {
            count++;
        }
    }
    return count;
}
```

**关键逻辑**：
- 入度：列遍历（`arcs[i][v]`）
- 出度：行遍历（`arcs[v][i]`）

### 6. 邻接表定位顶点

```c
int locate_vertex(adjlist *G, char v) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertex[i].tag == v) {
            return i;
        }
    }
    return -1;  // 未找到
}
```

---

## 复杂逻辑解释

### 入度和出度的区别

```
有向图：
A -> B -> C

邻接矩阵：
    A  B  C
A [ 0  1  0 ]
B [ 0  0  1 ]
C [ 0  0  0 ]

B 的入度 = 列 B 中 1 的个数 = 1（从 A 到 B）
B 的出度 = 行 B 中 1 的个数 = 1（从 B 到 C）
```

### 有向图 vs 无向图

```
无向图边的存储：
A - B

邻接矩阵：
    A  B
A [ 0  1 ]
B [ 1  0 ]

arcs[A][B] = arcs[B][A] = 1（对称）

有向图边的存储：
A -> B

邻接矩阵：
    A  B
A [ 0  1 ]
B [ 0  0 ]

arcs[A][B] = 1, arcs[B][A] = 0（不对称）
```

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| 入度/出度计算 | 入度列遍历，出度行遍历 |
| 有向图/无向图区别 | 无向图需要双向设置 |
| 顶点定位 | 需要先定位顶点再操作 |
| 边是否已存在 | 插入前检查 |
| 顶点是否已存在 | 插入前检查 |

---

## 复杂度总结

| 操作 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 插入顶点 | O(n) | O(1) |
| 插入边 | O(n) | O(1) |
| 计算入度 | O(n) | O(1) |
| 计算出度 | O(n) | O(1) |
| 定位顶点 | O(n) | O(1) |
