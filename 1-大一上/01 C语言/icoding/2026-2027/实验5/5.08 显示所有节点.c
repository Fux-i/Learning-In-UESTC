#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

void output_all_items(GoodsList *L) {
    GoodsList *p = L->next;

    while (p != NULL) {
        output_one_item(p);
        p = p->next;
    }
}
