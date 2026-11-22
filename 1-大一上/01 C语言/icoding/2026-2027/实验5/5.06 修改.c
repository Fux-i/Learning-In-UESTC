#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

bool change_item(GoodsList *L, char *goods_id, GoodsInfo new_info) {
    GoodsList *p = L->next;

    while (p != NULL) {
        if (strcmp(p->data.goods_id, goods_id) == 0) {
            p->data = new_info;
            return true;
        }
        p = p->next;
    }

    return false;
}
