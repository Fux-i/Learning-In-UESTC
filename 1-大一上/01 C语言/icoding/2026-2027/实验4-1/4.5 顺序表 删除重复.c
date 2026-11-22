#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
void del_dupnum(SeqList *L) {
    int i = 0;
    int j;

    if (L->last < 0) {
        return;
    }

    for (j = 1; j <= L->last; j++) {
        if (L->elem[j] != L->elem[i]) {
            i++;
            L->elem[i] = L->elem[j];
        }
    }

    L->last = i;
}
