#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

extern int CurrentCnt;

void destory_list(GoodsList **L) {
    GoodsList *p = *L;
    GoodsList *q;

    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }

    *L = NULL;
    CurrentCnt = 0;
}
