# 栈

## 核心考点

- 栈结构定义（数组栈、链栈）
- 栈的基本操作（push/pop/empty）
- 栈的应用：消除递归
- 栈在非递归遍历中的应用

---

## 必须会写的代码

1. 数组栈结构定义
2. 栈的基本操作
3. 用栈消除递归
4. 用栈实现非递归遍历

---

## 典型代码讲解

### 1. 数组栈结构定义

```c
#define Stack_Size 50

typedef int ElemType;

typedef struct {
    ElemType elem[Stack_Size];
    int top;  // 栈顶指针，指向栈顶元素
} Stack;
```

**要点**：
- `top` 指向栈顶元素
- 空栈时 `top = -1`
- 栈满时 `top = Stack_Size - 1`

### 2. 栈的基本操作

```c
// 初始化
void init_stack(Stack *S) {
    S->top = -1;
}

// 判空
bool is_empty(Stack *S) {
    return S->top == -1;
}

// 判满
bool is_full(Stack *S) {
    return S->top == Stack_Size - 1;
}

// 入栈
bool push(Stack *S, ElemType x) {
    if (is_full(S)) {
        return false;
    }
    S->elem[++S->top] = x;
    return true;
}

// 出栈
bool pop(Stack *S, ElemType *px) {
    if (is_empty(S)) {
        return false;
    }
    *px = S->elem[S->top--];
    return true;
}

// 获取栈顶
bool top(Stack *S, ElemType *px) {
    if (is_empty(S)) {
        return false;
    }
    *px = S->elem[S->top];
    return true;
}
```

**关键逻辑**：
- 入栈：`++top` 后赋值
- 出栈：赋值后 `top--`
- 判空：`top == -1`
- 判满：`top == Stack_Size - 1`

### 3. 链栈结构定义

```c
typedef struct _stack_node {
    ElemType data;
    struct _stack_node *next;
} StackNode, *LinkStack;
```

**特点**：
- 不需要判满（动态分配内存）
- 入栈出栈都在链表头部进行

### 4. 链栈操作

```c
// 初始化
void init_stack(LinkStack *S) {
    *S = NULL;
}

// 判空
bool is_empty(LinkStack *S) {
    return *S == NULL;
}

// 入栈（头插法）
bool push(LinkStack *S, ElemType x) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode) return false;
    newNode->data = x;
    newNode->next = *S;
    *S = newNode;
    return true;
}

// 出栈
bool pop(LinkStack *S, ElemType *px) {
    if (is_empty(S)) return false;
    StackNode *p = *S;
    *px = p->data;
    *S = p->next;
    free(p);
    return true;
}
```

### 5. 用栈消除递归（反转字符串）

**原递归代码**：
```c
void reverse() {
    char c = getchar();
    if (c == '.') return;
    reverse();
    putchar(c);
}
```

**用栈实现**：
```c
void reverse(Stack *S) {
    char c = getchar();
    while (c != '.') {
        push(S, c);
        c = getchar();
    }
    while (!is_empty(S)) {
        pop(S, &c);
        putchar(c);
    }
}
```

**原理**：
- 递归调用使用系统栈保存状态
- 用显式栈模拟递归过程
- 先压入所有字符，再依次弹出

### 6. 用栈实现非递归先序遍历

```c
void pre_order(BiTree root) {
    Stack S;
    init_stack(&S);
    push(&S, root);

    while (!is_empty(&S)) {
        BiTNode *node;
        pop(&S, &node);
        visit(node);

        // 先右后左入栈（因为栈是后进先出）
        if (node->right) push(&S, node->right);
        if (node->left) push(&S, node->left);
    }
}
```

**关键逻辑**：
- 先访问根结点，再处理子树
- 先右后左入栈，保证左子树先被访问
- 每次循环弹出一个结点并访问

---

## 复杂逻辑解释

### 为什么非递归先序遍历要先右后左入栈？

```
二叉树：
    A
   / \
  B   C

入栈顺序：
1. 先 push A
2. 弹出 A，访问 A
3. 先 push C（右），再 push B（左）
4. 栈：[C, B]（B 在栈顶）
5. 弹出 B，访问 B
6. 弹出 C，访问 C

结果：A -> B -> C（先序遍历）
```

如果先左后右入栈，访问顺序会变成 A -> C -> B。

### 递归转非递归的核心思想

递归函数调用时，系统会保存：
1. 返回地址
2. 局部变量
3. 函数参数

用栈模拟这个过程：
- 把递归调用变成入栈操作
- 把返回变成出栈操作

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| 栈空判断 | 出栈前检查 `top == -1` |
| 栈满判断 | 入栈前检查 `top == Stack_Size - 1` |
| top 指针位置 | `top` 指向栈顶元素，不是栈顶的下一个位置 |
| 非递归遍历入栈顺序 | 先右后左，保证左子树先访问 |
| 栈消除递归 | 先压入所有数据，再依次弹出 |

---

## 复杂度总结

| 操作 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 初始化 | O(1) | O(1) |
| 入栈 | O(1) | O(1) |
| 出栈 | O(1) | O(1) |
| 判空 | O(1) | O(1) |
| 非递归先序遍历 | O(n) | O(h)，h 为树高 |
