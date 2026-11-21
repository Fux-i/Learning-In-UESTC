#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
void del_x2y(SeqList *L, ElemType x, ElemType y) {
    int i;
    int k = 0;

    for (i = 0; i <= L->last; i++) {
        if (L->elem[i] < x || L->elem[i] > y) {
            L->elem[k] = L->elem[i];
            k++;
        }
    }

    L->last = k - 1;
}
