# 队列

## 核心考点

- 数组队列（循环队列）结构定义
- 循环队列的基本操作
- 队列在层序遍历中的应用
- 链表队列（已在链表模块介绍）

---

## 必须会写的代码

1. 循环队列结构定义
2. 循环队列入队出队
3. 队列在层序遍历中的应用

---

## 典型代码讲解

### 1. 循环队列结构定义

```c
#define MAXSIZE 100

typedef struct {
    int elem[MAXSIZE];
    int front;  // 队头指针
    int rear;   // 队尾指针
} SqQueue;
```

**要点**：
- `front` 指向队头元素
- `rear` 指向队尾元素的下一个位置
- 循环队列：`rear = (rear + 1) % MAXSIZE`

### 2. 循环队列基本操作

```c
// 初始化
void init_queue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
}

// 判空
bool is_empty(SqQueue *Q) {
    return Q->front == Q->rear;
}

// 判满（牺牲一个空间）
bool is_full(SqQueue *Q) {
    return (Q->rear + 1) % MAXSIZE == Q->front;
}

// 入队
bool enter_queue(SqQueue *Q, int x) {
    if (is_full(Q)) {
        return false;
    }
    Q->elem[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return true;
}

// 出队
bool leave_queue(SqQueue *Q, int *x) {
    if (is_empty(Q)) {
        return false;
    }
    *x = Q->elem[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return true;
}

// 队列长度
int queue_length(SqQueue *Q) {
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}
```

**关键逻辑**：
- 入队：`rear = (rear + 1) % MAXSIZE`
- 出队：`front = (front + 1) % MAXSIZE`
- 判空：`front == rear`
- 判满：`(rear + 1) % MAXSIZE == front`（牺牲一个空间）

### 3. 队列在层序遍历中的应用

```c
void level_order(BiTree root) {
    if (root == NULL) return;

    SqQueue Q;
    init_queue(&Q);
    enter_queue(&Q, root);

    while (!is_empty(&Q)) {
        BiTNode *node;
        leave_queue(&Q, &node);
        visit(node);

        if (node->left) enter_queue(&Q, node->left);
        if (node->right) enter_queue(&Q, node->right);
    }
}
```

**关键逻辑**：
- 根结点入队
- 循环：出队并访问，将子结点入队
- 队列保证了按层次顺序访问

---

## 复杂逻辑解释

### 为什么循环队列要牺牲一个空间？

```
如果不用循环：
rear - front = 队列长度

如果用循环（不牺牲空间）：
判满条件：rear == front
判空条件：rear == front
两者相同，无法区分！

牺牲一个空间后：
判满条件：(rear + 1) % MAXSIZE == front
判空条件：rear == front
可以区分了。
```

### 循环队列的取模运算

```
MAXSIZE = 100
当前 rear = 99

入队一个元素：
rear = (99 + 1) % 100 = 0

这样 rear 就回到了数组开头，实现了循环。
```

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| 判满条件 | `(rear + 1) % MAXSIZE == front`，不是 `rear == front` |
| 判空条件 | `front == rear` |
| 入队后更新 rear | `rear = (rear + 1) % MAXSIZE` |
| 出队后更新 front | `front = (front + 1) % MAXSIZE` |
| 队列长度计算 | `(rear - front + MAXSIZE) % MAXSIZE` |

---

## 复杂度总结

| 操作 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 初始化 | O(1) | O(1) |
| 入队 | O(1) | O(1) |
| 出队 | O(1) | O(1) |
| 判空 | O(1) | O(1) |
| 层序遍历 | O(n) | O(n) |
