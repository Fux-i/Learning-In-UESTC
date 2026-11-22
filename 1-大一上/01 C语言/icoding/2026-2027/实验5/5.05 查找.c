#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

GoodsList *search_item(GoodsList *L, char *goods_id) {
    GoodsList *p = L->next;

    while (p != NULL) {
        if (strcmp(p->data.goods_id, goods_id) == 0) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}
