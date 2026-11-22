#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
int compute_reverse_polish_notation(char *str) {
    Stack s;
    ElemType a, b, v;
    char token[64];
    int n;
    char *p = str;

    init_stack(&s);

    while (*p) {
        while (*p == ' ')
            p++;
        if (!*p)
            break;

        n = 0;
        while (*p && *p != ' ') {
            if (n < 63)
                token[n++] = *p;
            p++;
        }
        token[n] = '\0';

        if (n == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' ||
                       token[0] == '%')) {
            if (!pop(&s, &b))
                return 0;
            if (!pop(&s, &a))
                return 0;
            switch (token[0]) {
            case '+':
                v = a + b;
                break;
            case '-':
                v = a - b;
                break;
            case '*':
                v = a * b;
                break;
            case '/':
                v = a / b;
                break;
            default:
                v = a % b;
                break;
            }
            push(&s, v);
        } else {
            push(&s, (ElemType)atoi(token));
        }
    }

    if (!pop(&s, &v))
        return 0;
    return (int)v;
}
