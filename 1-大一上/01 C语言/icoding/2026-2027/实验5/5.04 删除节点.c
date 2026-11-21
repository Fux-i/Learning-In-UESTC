#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

extern int CurrentCnt;

bool delete_item(GoodsList *L, char *goods_id) {
    GoodsList *p = L;
    GoodsList *q;

    while (p->next != NULL) {
        if (strcmp(p->next->data.goods_id, goods_id) == 0) {
            q = p->next;
            p->next = q->next;
            free(q);
            CurrentCnt--;
            return true;
        }
        p = p->next;
    }

    return false;
}
