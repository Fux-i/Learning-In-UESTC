# 图的算法

## 核心考点

- Prim 最小生成树（手算）
- Kruskal 最小生成树（手算）
- 关键路径（手算 + 代码）
- 欧拉通路判断

---

## 必须会写的代码

1. Prim 算法手算
2. Kruskal 算法手算
3. 关键路径计算
4. 欧拉通路判断

---

## 典型代码讲解

### 1. Prim 最小生成树（手算）

**算法步骤**：
1. 从任意顶点开始（通常从 0）
2. 找到当前已选顶点集合到未选顶点的最小边
3. 将该边和对应顶点加入集合
4. 重复直到所有顶点都加入

**示例**：
```
图：
    0
   /|\
  1-+--2
   \|/
    3

边权：
0-1: 6
0-2: 1
0-3: 5
1-2: 5
1-3: 4
2-3: 2

Prim 从 0 开始：
1. 选 0-2 (权 1)
2. 选 2-3 (权 2)
3. 选 3-1 (权 4)

最小生成树：0-2-3-1，总权 = 1 + 2 + 4 = 7
```

### 2. Kruskal 最小生成树（手算）

**算法步骤**：
1. 将所有边按权值排序
2. 依次选择权值最小的边
3. 如果该边不会形成环，则加入
4. 重复直到有 n-1 条边

**示例**（同上图）：
```
边排序：
0-2: 1
2-3: 2
1-3: 4
0-1: 6
0-3: 5
1-2: 5

选择过程：
1. 选 0-2 (权 1)，不形成环
2. 选 2-3 (权 2)，不形成环
3. 选 1-3 (权 4)，不形成环
4. 已有 3 条边（n-1=3），完成

最小生成树：0-2-3-1，总权 = 1 + 2 + 4 = 7
```

### 3. 关键路径（AOE 网）

**相关概念**：
- AOE 网：边表示活动，顶点表示事件
- 关键路径：从源点到汇点的最长路径
- 关键活动：关键路径上的活动

**计算步骤**：
1. 计算各顶点的最早发生时间 `etv`（正向）
2. 计算各顶点的最迟发生时间 `ltv`（逆向）
3. 计算各活动的最早开始时间 `ete`
4. 计算各活动的最迟开始时间 `lte`
5. `ete == lte` 的活动是关键活动

**代码实现**：
```c
// 计算最早发生时间 etv
void get_etv(MatrixGraph *G, int etv[]) {
    // 初始化
    for (int i = 0; i < G->vexnum; i++) {
        etv[i] = 0;
    }
    // 正向计算
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            if (G->arcs[i][j] != 0) {
                if (etv[i] + G->arcs[i][j] > etv[j]) {
                    etv[j] = etv[i] + G->arcs[i][j];
                }
            }
        }
    }
}

// 计算最迟发生时间 ltv
void get_ltv(MatrixGraph *G, int etv[], int ltv[]) {
    int max_etv = 0;
    // 找到最大 etv 作为汇点时间
    for (int i = 0; i < G->vexnum; i++) {
        if (etv[i] > max_etv) {
            max_etv = etv[i];
        }
    }
    // 初始化 ltv
    for (int i = 0; i < G->vexnum; i++) {
        ltv[i] = max_etv;
    }
    // 逆向计算
    for (int i = G->vexnum - 1; i >= 0; i--) {
        for (int j = 0; j < G->vexnum; j++) {
            if (G->arcs[i][j] != 0) {
                if (ltv[j] - G->arcs[i][j] < ltv[i]) {
                    ltv[i] = ltv[j] - G->arcs[i][j];
                }
            }
        }
    }
}
```

### 4. 欧拉通路判断

**欧拉通路条件**（有向图）：
1. 所有顶点的入度和出度之差的绝对值不超过 1
2. 入度比出度大 1 的顶点个数为 0 或 1
3. 出度比入度大 1 的顶点个数为 0 或 1

**代码实现**：
```c
bool if_eulerpath(MatrixGraph *G) {
    int n = G->vexnum;
    int *indeg = (int *)malloc(n * sizeof(int));
    int *outdeg = (int *)malloc(n * sizeof(int));

    // 计算入度和出度
    for (int i = 0; i < n; i++) {
        indeg[i] = 0;
        outdeg[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G->arcs[i][j] != 0) {
                outdeg[i]++;
                indeg[j]++;
            }
        }
    }

    // 判断条件
    int diff_count = 0;
    for (int i = 0; i < n; i++) {
        int diff = indeg[i] - outdeg[i];
        if (diff > 1 || diff < -1) {
            free(indeg);
            free(outdeg);
            return false;
        }
        if (diff == 1 || diff == -1) {
            diff_count++;
        }
    }

    free(indeg);
    free(outdeg);
    return (diff_count == 0 || diff_count == 2);
}
```

---

## 复杂逻辑解释

### Prim 和 Kruskal 的区别

| 算法 | 适用场景 | 时间复杂度 | 特点 |
|------|----------|------------|------|
| Prim | 稠密图 | O(n²) | 从顶点出发，逐步扩展 |
| Kruskal | 稀疏图 | O(eloge) | 从边出发，依次选择 |

### 关键路径的计算过程

```
AOE 网：
    0 --4--> 1 --5--> 2
    |                 |
    6                 4
    |                 |
    v                 v
    2 --3--> 3 --3--> 5

计算 etv（最早发生时间）：
etv[0] = 0
etv[1] = max(etv[0]+4) = 4
etv[2] = max(etv[0]+6) = 6
etv[3] = max(etv[2]+3) = 9
etv[4] = max(etv[1]+5, etv[2]+4) = max(9, 10) = 10
etv[5] = max(etv[3]+3, etv[4]+3) = max(12, 13) = 13

计算 ltv（最迟发生时间）：
ltv[5] = 13
ltv[4] = ltv[5]-3 = 10
ltv[3] = ltv[5]-3 = 10
ltv[2] = min(ltv[3]-3, ltv[4]-4) = min(7, 6) = 6
ltv[1] = ltv[4]-5 = 5
ltv[0] = min(ltv[1]-4, ltv[2]-6) = min(1, 0) = 0

关键路径：etv[i] == ltv[i] 的顶点
```

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| Prim 算法起始点 | 可以从任意顶点开始 |
| Kruskal 算法环检测 | 选择边时要检查是否形成环 |
| 关键路径 etv 计算 | 正向计算，取最大值 |
| 关键路径 ltv 计算 | 逆向计算，取最小值 |
| 欧拉通路条件 | 入度出度差不超过 1，差为 ±1 的顶点数为 0 或 2 |

---

## 复杂度总结

| 算法 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| Prim | O(n²) | O(n) |
| Kruskal | O(eloge) | O(e) |
| 关键路径 | O(n²) | O(n) |
| 欧拉通路 | O(n²) | O(n) |
