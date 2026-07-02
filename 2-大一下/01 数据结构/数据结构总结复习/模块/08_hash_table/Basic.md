# 哈希表

## 核心考点

- 哈希函数（取模法）
- 线性探测法解决冲突
- 链址法解决冲突
- 哈希表插入操作
- 哈希排序

---

## 必须会写的代码

1. 线性探测法
2. 链址法
3. 哈希表插入
4. 哈希排序

---

## 典型代码讲解

### 1. 哈希函数

```c
// 最简单的哈希函数：取模法
int hash(int key, int m) {
    return key % m;
}
```

**要点**：
- `m` 通常取质数
- 哈希函数应尽量均匀分布

### 2. 线性探测法

```c
#define SIZE 13

void linear_probe(int hashTable[], int keys[], int n) {
    for (int i = 0; i < n; i++) {
        int key = keys[i] % SIZE;
        // 线性探测：找下一个空位
        while (hashTable[key] != 0) {
            key = (key + 1) % SIZE;
        }
        hashTable[key] = keys[i];
    }
}
```

**关键逻辑**：
- 发生冲突时，依次检查下一个位置
- 使用取模实现循环
- 直到找到空位

### 3. 链址法

```c
typedef struct hashnode {
    int key;
    struct hashnode *next;
} hashnode;

void chaining(hashnode *ht[], int keys[], int n, int P) {
    for (int i = 0; i < n; i++) {
        // 创建新结点
        hashnode *newnode = (hashnode *)malloc(sizeof(hashnode));
        newnode->key = keys[i];
        newnode->next = NULL;

        // 计算哈希值
        int hashval = keys[i] % P;

        // 头插法插入链表
        if (ht[hashval] == NULL) {
            ht[hashval] = newnode;
        } else {
            newnode->next = ht[hashval];
            ht[hashval] = newnode;
        }
    }
}
```

**关键逻辑**：
- 每个槽位是一个链表
- 冲突时用头插法插入链表
- 头插法时间复杂度 O(1)

### 4. 哈希排序（利用无重复值）

```c
void hash_sort(unsigned *a, unsigned n) {
    if (n == 0) return;

    // 找到最大值 m
    unsigned m = 0;
    for (unsigned i = 0; i < n; i++) {
        if (a[i] > m) m = a[i];
    }

    // 创建计数数组
    unsigned *count = (unsigned *)calloc(m + 1, sizeof(unsigned));

    // 计数
    for (unsigned i = 0; i < n; i++) {
        count[a[i]]++;
    }

    // 收集
    unsigned index = 0;
    for (unsigned i = 1; i <= m; i++) {
        while (count[i] > 0) {
            a[index++] = i;
            count[i]--;
        }
    }

    free(count);
}
```

**关键逻辑**：
- 利用无重复值的特点
- `hash(K) = K` 直接映射
- 时间复杂度 O(m)，空间复杂度 O(m)

---

## 复杂逻辑解释

### 线性探测法的探测过程

```
哈希表大小：5
插入序列：10, 15, 20, 25, 30

插入 10: hash(10) = 10 % 5 = 0
表：[10, _, _, _, _]

插入 15: hash(15) = 15 % 5 = 0
冲突！探测 1：位置 0 被占，检查位置 1
表：[10, 15, _, _, _]

插入 20: hash(20) = 20 % 5 = 0
冲突！探测 1：位置 0 被占，检查位置 1
冲突！探测 2：位置 1 被占，检查位置 2
表：[10, 15, 20, _, _]

插入 25: hash(25) = 25 % 5 = 0
冲突！探测 1-3：位置 0-2 被占，检查位置 3
表：[10, 15, 20, 25, _]

插入 30: hash(30) = 30 % 5 = 0
冲突！探测 1-4：位置 0-3 被占，检查位置 4
表：[10, 15, 20, 25, 30]
```

### 链址法的冲突处理

```
哈希表大小：5
插入序列：10, 15, 20, 25, 30

插入 10: hash(10) = 0
ht[0] -> [10]

插入 15: hash(15) = 0（冲突）
头插法：ht[0] -> [15] -> [10]

插入 20: hash(20) = 0（冲突）
头插法：ht[0] -> [20] -> [15] -> [10]

插入 25: hash(25) = 0（冲突）
头插法：ht[0] -> [25] -> [20] -> [15] -> [10]

插入 30: hash(30) = 0（冲突）
头插法：ht[0] -> [30] -> [25] -> [20] -> [15] -> [10]
```

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| 线性探测循环取模 | `key = (key + 1) % SIZE` |
| 链址法用头插法 | 不是尾插法 |
| 哈希表长度选择 | 通常取质数 |
| 哈希排序无重复值 | 利用 `hash(K) = K` 特性 |
| 内存分配检查 | malloc 后检查是否为 NULL |

---

## 复杂度总结

| 操作 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 线性探测插入 | O(n) | O(m) |
| 链址法插入 | O(1) | O(n + m) |
| 哈希排序 | O(m) | O(m) |
| 查找（平均） | O(1) | - |
| 查找（最坏） | O(n) | - |
