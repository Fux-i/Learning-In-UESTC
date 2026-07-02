/*
 * 题目：栈的基本操作
 * 来源：原 Todo
 * 要求：实现数组栈的基本操作
 *
 * 函数声明：
 *   void init_stack(Stack *S);
 *   bool push(Stack *S, ElemType x);
 *   bool pop(Stack *S, ElemType *px);
 *   bool is_empty(Stack *S);
 *
 * TODO: 补全四个函数
 */

#include <stdio.h>
#include <stdbool.h>

#define Stack_Size 50

typedef int ElemType;

typedef struct {
    ElemType elem[Stack_Size];
    int top;  // 栈顶指针，指向栈顶元素
} Stack;

// TODO: 补全初始化操作
void init_stack(Stack *S) {
    // TODO: 在此补全代码

}

// TODO: 补全判空操作
bool is_empty(Stack *S) {
    // TODO: 在此补全代码

}

// TODO: 补全入栈操作
// 注意：需要检查栈满
bool push(Stack *S, ElemType x) {
    // TODO: 在此补全代码

}

// TODO: 补全出栈操作
// 注意：需要检查栈空
bool pop(Stack *S, ElemType *px) {
    // TODO: 在此补全代码

}

int main() {
    Stack S;
    ElemType x;

    // 初始化
    init_stack(&S);
    printf("栈是否为空：%s\n", is_empty(&S) ? "是" : "否");  // 预期：是

    // 入栈测试
    push(&S, 10);
    push(&S, 20);
    push(&S, 30);
    printf("入栈 10, 20, 30 后，栈是否为空：%s\n", is_empty(&S) ? "是" : "否");  // 预期：否

    // 出栈测试
    pop(&S, &x);
    printf("出栈元素：%d\n", x);  // 预期：30
    pop(&S, &x);
    printf("出栈元素：%d\n", x);  // 预期：20

    // 测试栈空
    pop(&S, &x);
    printf("出栈元素：%d\n", x);  // 预期：10
    printf("栈是否为空：%s\n", is_empty(&S) ? "是" : "否");  // 预期：是

    // 测试栈空时出栈
    bool result = pop(&S, &x);
    printf("栈空时出栈结果：%s\n", result ? "成功" : "失败");  // 预期：失败

    return 0;
}
