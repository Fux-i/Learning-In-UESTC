# 顺序表

## 核心考点

- 顺序表结构定义（数组 + last 域）
- 插入操作（指定位置插入）
- 删除操作（按值/按条件删除）
- 合并操作（两个有序表合并）
- 分割操作（按位置/条件分裂）
- 双指针法（原地删除/保留元素）

---

## 必须会写的代码

1. 顺序表结构定义
2. 初始化操作
3. 插入操作
4. 删除操作
5. 合并两个有序表
6. 双指针法删除/保留元素

---

## 典型代码讲解

### 1. 顺序表结构定义

```c
#define MAXSIZE 100

typedef struct {
    int elem[MAXSIZE];  // 存储数据的数组
    int last;           // 最后一个元素的下标，空表时为 -1
} SeqList;
```

**要点**：
- `last` 域表示最后一个元素的下标
- 空表时 `last = -1`
- 表长为 `last + 1`

### 2. 初始化操作

```c
void initList(SeqList *L) {
    L->last = -1;
}
```

### 3. 插入操作（在位置 pos 插入元素 x）

```c
bool insert(SeqList *L, int pos, int x) {
    // 检查表满
    if (L->last >= MAXSIZE - 1) {
        return false;
    }
    // 检查位置合法性
    if (pos < 0 || pos > L->last + 1) {
        return false;
    }
    // 从后往前移动元素
    for (int i = L->last; i >= pos; i--) {
        L->elem[i + 1] = L->elem[i];
    }
    // 插入新元素
    L->elem[pos] = x;
    // 更新 last
    L->last++;
    return true;
}
```

**关键逻辑**：
- 从后往前移动，避免覆盖
- 移动次数：`L->last - pos + 1`
- 时间复杂度：O(n)

### 4. 删除操作（删除位置 pos 的元素）

```c
bool delete(SeqList *L, int pos, int *x) {
    // 检查表空
    if (L->last == -1) {
        return false;
    }
    // 检查位置合法性
    if (pos < 0 || pos > L->last) {
        return false;
    }
    // 保存被删元素
    *x = L->elem[pos];
    // 从前往后移动元素
    for (int i = pos; i < L->last; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    // 更新 last
    L->last--;
    return true;
}
```

**关键逻辑**：
- 从前往后移动，避免覆盖
- 移动次数：`L->last - pos`
- 时间复杂度：O(n)

### 5. 合并两个有序表

```c
void merge(SeqList *LA, SeqList *LB, SeqList *LC) {
    int i = 0, j = 0, k = 0;
    // 依次比较，取较小值
    while (i <= LA->last && j <= LB->last) {
        if (LA->elem[i] < LB->elem[j]) {
            LC->elem[k++] = LA->elem[i++];
        } else {
            LC->elem[k++] = LB->elem[j++];
        }
    }
    // 处理剩余元素
    while (i <= LA->last) {
        LC->elem[k++] = LA->elem[i++];
    }
    while (j <= LB->last) {
        LC->elem[k++] = LB->elem[j++];
    }
    LC->last = k - 1;
}
```

**关键逻辑**：
- 双指针 i, j 分别指向两个表
- 比较后取较小值，指针后移
- 最后处理剩余元素
- 时间复杂度：O(n + m)

### 6. 双指针法删除元素

```c
// 删除所有能被 f 整除的元素
void remove_elem(SeqList *L, int f) {
    int i = 0, j = 0;
    while (i <= L->last) {
        if (L->elem[i] % f != 0) {
            L->elem[j++] = L->elem[i];
        }
        i++;
    }
    L->last = j - 1;
}
```

**关键逻辑**：
- i 是遍历指针，j 是写入指针
- 保留的元素复制到 j 的位置
- 最后更新 last 域
- 时间复杂度：O(n)，空间复杂度：O(1)

---

## 复杂逻辑解释

### 插入操作为什么从后往前移动？

如果从前往后移动：
```
原数组：[1, 2, 3, 4, 5]
在位置 2 插入 99

从前往后移动：
elem[3] = elem[2]  // 3 被覆盖为 4
elem[4] = elem[3]  // 4 被覆盖为 5
结果：[1, 2, 4, 5, 5]  // 错误！3 丢失了
```

从后往前移动：
```
原数组：[1, 2, 3, 4, 5]
在位置 2 插入 99

从后往前移动：
elem[5] = elem[4]  // 5 移动到位置 5
elem[4] = elem[3]  // 4 移动到位置 4
elem[3] = elem[2]  // 3 移动到位置 3
然后：elem[2] = 99
结果：[1, 2, 99, 3, 4, 5]  // 正确
```

### 双指针法的原理

```
原数组：[1, 2, 3, 4, 5, 6]
删除偶数

i=0, j=0: elem[0]=1 (奇数) → elem[0]=1, j=1
i=1, j=1: elem[1]=2 (偶数) → 跳过
i=2, j=1: elem[2]=3 (奇数) → elem[1]=3, j=2
i=3, j=2: elem[3]=4 (偶数) → 跳过
i=4, j=2: elem[4]=5 (奇数) → elem[2]=5, j=3
i=5, j=3: elem[5]=6 (偶数) → 跳过

结果：[1, 3, 5, ...]，last = 2
```

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| 表满判断 | 插入前检查 `last >= MAXSIZE - 1` |
| 表空判断 | 删除前检查 `last == -1` |
| 位置合法性 | 插入：`0 <= pos <= last+1`；删除：`0 <= pos <= last` |
| last 域更新 | 插入后 `last++`，删除后 `last--` |
| 合并时剩余元素 | 循环结束后还要处理两个表的剩余元素 |
| 双指针法最后更新 last | 别忘了 `L->last = j - 1` |

---

## 复杂度总结

| 操作 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 初始化 | O(1) | O(1) |
| 插入 | O(n) | O(1) |
| 删除 | O(n) | O(1) |
| 合并 | O(n + m) | O(1) |
| 双指针法删除 | O(n) | O(1) |
