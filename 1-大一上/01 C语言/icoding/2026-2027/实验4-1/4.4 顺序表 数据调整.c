#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
void odd_even(SeqList *L) {
    int i = 0;
    int j = L->last;
    ElemType tmp;

    while (i < j) {
        if (L->elem[i] % 2 != 0) {
            i++;
        } else if (L->elem[j] % 2 == 0) {
            j--;
        } else {
            tmp = L->elem[i];
            L->elem[i] = L->elem[j];
            L->elem[j] = tmp;
            i++;
            j--;
        }
    }
}
