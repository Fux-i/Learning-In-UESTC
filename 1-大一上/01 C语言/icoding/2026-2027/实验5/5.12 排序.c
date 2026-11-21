#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

void bubble_sort(GoodsList *L) {
    GoodsList *i;
    GoodsList *j;
    GoodsInfo tmp;

    for (i = L->next; i != NULL && i->next != NULL; i = i->next) {
        for (j = L->next; j->next != NULL; j = j->next) {
            if (j->data.goods_price > j->next->data.goods_price) {
                tmp = j->data;
                j->data = j->next->data;
                j->next->data = tmp;
            }
        }
    }
}
