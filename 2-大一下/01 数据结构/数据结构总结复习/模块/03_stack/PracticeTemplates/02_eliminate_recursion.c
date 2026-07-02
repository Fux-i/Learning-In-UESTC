/*
 * 题目：用栈消除递归
 * 来源：真题178
 * 要求：用栈实现字符串反转（消除递归）
 *
 * 原递归代码：
 *   void reverse() {
 *       char c = getchar();
 *       if (c == '.') return;
 *       reverse();
 *       putchar(c);
 *   }
 *
 * 功能：将输入的字符序列（以'.'结尾）倒序输出（不包括'.'）
 * 示例：输入 "abc123." 输出 "321cba"
 *
 * 函数声明：
 *   void reverse(Stack *S);
 *
 * 参数说明：
 *   S: 指向已初始化的栈的指针
 *
 * TODO: 补全 reverse 函数
 */

#include <stdio.h>
#include <stdbool.h>

#define Stack_Size 100

typedef char ElemType;

typedef struct {
    ElemType elem[Stack_Size];
    int top;
} Stack;

void init_stack(Stack *S) {
    S->top = -1;
}

bool is_empty(Stack *S) {
    return S->top == -1;
}

bool push(Stack *S, ElemType x) {
    if (S->top >= Stack_Size - 1) return false;
    S->elem[++S->top] = x;
    return true;
}

bool pop(Stack *S, ElemType *px) {
    if (S->top == -1) return false;
    *px = S->elem[S->top--];
    return true;
}

// TODO: 补全反转操作
// 用栈消除递归，功能与原递归函数相同
// 提示：1. 先读取所有字符压入栈 2. 再依次弹出并输出
void reverse(Stack *S) {
    // TODO: 在此补全代码

}

int main() {
    Stack S;
    init_stack(&S);

    printf("请输入字符序列（以'.'结尾）：");
    // 测试输入：abc123.
    // 预期输出：321cba
    reverse(&S);
    printf("\n");

    return 0;
}
