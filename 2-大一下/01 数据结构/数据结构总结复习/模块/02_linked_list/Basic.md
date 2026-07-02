# 链表

## 核心考点

- 单链表结构定义（结点 + 指针）
- 头插法、尾插法建表
- 插入操作（前插、后插）
- 删除操作（按值、按位置）
- 链表分割（分裂为两个链表）
- 循环链表操作
- 共享结点问题

---

## 必须会写的代码

1. 单链表结构定义
2. 头插法建表
3. 尾插法建表
4. 按位置插入
5. 按值删除
6. 链表分割
7. 循环链表队列

---

## 典型代码讲解

### 1. 单链表结构定义

```c
typedef struct _node {
    int data;           // 数据域
    struct _node *next; // 指针域
} node;

typedef struct {
    node *head;      // 头指针
    unsigned len;    // 链表长度
} list;
```

**要点**：
- 结点包含数据域和指针域
- 链表结构包含头指针和长度

### 2. 头插法建表

```c
// 头插法：新结点插入到头部
void insert_head(list *L, int x) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = x;
    newNode->next = L->head;
    L->head = newNode;
    L->len++;
}
```

**特点**：
- 结点顺序与输入顺序相反
- 时间复杂度：O(1)

### 3. 尾插法建表

```c
// 尾插法：新结点插入到尾部
void insert_tail(list *L, int x) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = x;
    newNode->next = NULL;

    if (L->head == NULL) {
        L->head = newNode;
    } else {
        node *p = L->head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }
    L->len++;
}
```

**特点**：
- 结点顺序与输入顺序相同
- 时间复杂度：O(n)

### 4. 按位置插入（前插法）

```c
// 在位置 pos 插入元素 x（从 0 开始）
bool insert(list *L, int pos, int x) {
    if (pos < 0 || pos > L->len) {
        return false;
    }

    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = x;

    if (pos == 0) {
        // 插入头部
        newNode->next = L->head;
        L->head = newNode;
    } else {
        // 找到位置 pos-1 的结点
        node *p = L->head;
        for (int i = 0; i < pos - 1; i++) {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
    L->len++;
    return true;
}
```

**关键逻辑**：
- 插入头部需要特殊处理
- 其他位置需要找到前驱结点
- 先连后断：先设置新结点的 next，再修改前驱的 next

### 5. 按值删除

```c
// 删除第一个值为 x 的结点
bool delete_by_value(list *L, int x) {
    if (L->head == NULL) {
        return false;
    }

    node *p = L->head;
    node *pre = NULL;

    // 找到值为 x 的结点及其前驱
    while (p != NULL && p->data != x) {
        pre = p;
        p = p->next;
    }

    if (p == NULL) {
        return false;  // 未找到
    }

    if (pre == NULL) {
        // 删除的是头结点
        L->head = p->next;
    } else {
        // 删除的是中间或尾部结点
        pre->next = p->next;
    }
    free(p);
    L->len--;
    return true;
}
```

**关键逻辑**：
- 需要两个指针：p 指向当前结点，pre 指向前驱
- 删除头结点需要特殊处理
- 别忘了 free 释放内存

### 6. 链表分割

```c
// 将链表 L 分割成 L1 和 L2
// L1 包含前 pos 个结点，L2 包含剩余结点
void split(list *L, int pos, list *L1, list *L2) {
    if (pos <= 0 || pos >= L->len) {
        return;
    }

    // 找到位置 pos-1 的结点
    node *p = L->head;
    for (int i = 0; i < pos - 1; i++) {
        p = p->next;
    }

    // L1 的头就是 L 的头
    L1->head = L->head;
    L1->len = pos;

    // L2 的头是位置 pos 的结点
    L2->head = p->next;
    L2->len = L->len - pos;

    // 断开连接
    p->next = NULL;
}
```

### 7. 循环链表队列

```c
typedef struct _QueueNode {
    int data;
    struct _QueueNode *next;
} LinkQueueNode, *LinkQueue;

// 初始化（带头结点，循环）
bool init_queue(LinkQueue *LQ) {
    *LQ = (LinkQueue)malloc(sizeof(LinkQueueNode));
    if (!*LQ) return false;
    (*LQ)->next = *LQ;  // 指向自己，形成循环
    return true;
}

// 入队（尾插法）
bool enter_queue(LinkQueue *LQ, int x) {
    LinkQueueNode *newNode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (!newNode) return false;
    newNode->data = x;
    newNode->next = *LQ;  // 新结点指向头结点

    // 找到队尾（最后一个结点）
    LinkQueueNode *tail = *LQ;
    while (tail->next != *LQ) {
        tail = tail->next;
    }
    tail->next = newNode;  // 队尾指向新结点
    return true;
}

// 出队（删除第一个结点）
bool leave_queue(LinkQueue *LQ, int *x) {
    if ((*LQ)->next == *LQ) {
        return false;  // 队列为空
    }
    LinkQueueNode *head = (*LQ)->next;
    *x = head->data;
    (*LQ)->next = head->next;  // 头结点指向第二个结点
    free(head);
    return true;
}
```

**关键逻辑**：
- 循环链表：最后一个结点的 next 指向头结点
- 判空条件：`head->next == head`
- 入队需要找到队尾（遍历）
- 出队删除第一个结点（头结点的下一个）

---

## 复杂逻辑解释

### 为什么删除操作需要前驱指针？

单链表无法向前遍历，删除结点需要修改前驱的 next 指针：

```
删除结点 B：
A -> B -> C

需要：
1. 找到 B 的前驱 A
2. 让 A->next = B->next
3. free(B)

结果：
A -> C
```

如果删除的是头结点，没有前驱，需要特殊处理。

### 循环链表队列的判空

```
空队列（只有头结点）：
head -> head（指向自己）

head->next == head  // 判空条件
```

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| 空链表判断 | 操作前检查 `head == NULL` |
| 头结点处理 | 插入/删除头部需要特殊处理 |
| 前驱指针 | 删除操作需要找到前驱 |
| 内存释放 | 删除结点后要 `free` |
| 循环链表终止条件 | `p->next != head` 而不是 `p->next != NULL` |
| 循环链表判空 | `head->next == head` |

---

## 复杂度总结

| 操作 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 头插法建表 | O(n) | O(1) |
| 尾插法建表 | O(n) | O(1) |
| 按位置插入 | O(n) | O(1) |
| 按值删除 | O(n) | O(1) |
| 链表分割 | O(n) | O(1) |
| 循环链表入队 | O(n) | O(1) |
| 循环链表出队 | O(1) | O(1) |
