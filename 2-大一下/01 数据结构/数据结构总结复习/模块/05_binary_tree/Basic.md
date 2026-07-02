# 二叉树遍历

## 核心考点

- 二叉树结构定义
- 递归先序/中序/后序遍历
- 非递归先序遍历（用栈）
- 层序遍历（用队列）
- 镜像二叉树
- 二叉排序树（BST）

---

## 必须会写的代码

1. 二叉树结构定义
2. 递归先序遍历
3. 非递归先序遍历
4. 层序遍历
5. 镜像二叉树
6. BST 插入

---

## 典型代码讲解

### 1. 二叉树结构定义

```c
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} BiTNode, *BiTree;
```

### 2. 递归先序遍历

```c
void pre_order(BiTree root) {
    if (root == NULL) return;
    visit(root);           // 访问根结点
    pre_order(root->left); // 遍历左子树
    pre_order(root->right);// 遍历右子树
}
```

**遍历顺序**：
- 先序：根 -> 左 -> 右
- 中序：左 -> 根 -> 右
- 后序：左 -> 右 -> 根

### 3. 非递归先序遍历

```c
void pre_order(BiTree root) {
    Stack S;
    init_stack(&S);
    push(&S, root);

    while (!is_empty(&S)) {
        BiTNode *node;
        pop(&S, &node);
        visit(node);

        // 先右后左入栈
        if (node->right) push(&S, node->right);
        if (node->left) push(&S, node->left);
    }
}
```

**关键逻辑**：
- 根结点先入栈
- 每次弹出栈顶并访问
- 先右后左入栈（栈是后进先出）

### 4. 层序遍历

```c
void level_order(BiTree root) {
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
- 每次出队并访问，将子结点入队
- 队列保证按层次顺序访问

### 5. 镜像二叉树

```c
// 递归方法：交换左右子树
BiTree mirror(BiTree root) {
    if (root == NULL) return NULL;

    BiTree new_root = (BiTree)malloc(sizeof(BiTNode));
    new_root->data = root->data;
    new_root->left = mirror(root->right);  // 左子树是原右子树的镜像
    new_root->right = mirror(root->left);  // 右子树是原左子树的镜像
    return new_root;
}
```

### 6. 二叉排序树（BST）

```c
// BST 插入
BiTree bst_insert(BiTree root, int x) {
    if (root == NULL) {
        BiTree node = (BiTree)malloc(sizeof(BiTNode));
        node->data = x;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (x < root->data) {
        root->left = bst_insert(root->left, x);
    } else if (x > root->data) {
        root->right = bst_insert(root->right, x);
    }
    return root;
}

// BST 中序遍历（有序）
void bst_inorder(BiTree root) {
    if (root == NULL) return;
    bst_inorder(root->left);
    visit(root);
    bst_inorder(root->right);
}
```

**特点**：
- 左子树所有结点 < 根结点
- 右子树所有结点 > 根结点
- 中序遍历得到有序序列

---

## 复杂逻辑解释

### 非递归先序遍历的入栈顺序

```
二叉树：
    A
   / \
  B   C
 / \
D   E

先序遍历：A B D E C

入栈过程：
1. push A
2. pop A, visit A, push C, push B
3. pop B, visit B, push E, push D
4. pop D, visit D
5. pop E, visit E
6. pop C, visit C

结果：A B D E C ✓
```

如果先左后右入栈：
1. push A
2. pop A, visit A, push B, push C
3. pop C, visit C
4. pop B, visit B

结果：A C B ✗

### 层序遍历的队列作用

```
二叉树：
    A
   / \
  B   C

层序遍历：A B C

队列变化：
1. 入队 A
2. 出队 A, visit A, 入队 B, C
3. 出队 B, visit B
4. 出队 C, visit C

结果：A B C ✓
```

---

## 易错点

| 易错点 | 说明 |
|--------|------|
| 空树判断 | 遍历前检查 `root == NULL` |
| 非递归遍历入栈顺序 | 先右后左，不是先左后右 |
| 层序遍历用队列 | 不是用栈 |
| BST 插入重复值 | 通常不插入重复值 |
| 镜像二叉树 | 是新建一棵树，不是修改原树 |

---

## 复杂度总结

| 操作 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 递归遍历 | O(n) | O(h)，h 为树高 |
| 非递归先序遍历 | O(n) | O(h) |
| 层序遍历 | O(n) | O(w)，w 为树宽 |
| 镜像二叉树 | O(n) | O(h) |
| BST 插入 | O(h) | O(1) |
