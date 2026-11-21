#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

int save_to_file(GoodsList *L) {
    FILE *fp;
    GoodsList *p;
    int count = 0;

    fp = fopen("goodsinfo.txt", "w");
    if (fp == NULL) {
        return 0;
    }

    for (p = L->next; p != NULL; p = p->next) {
        fprintf(fp, "%s\t%s\t%d\t%s\t%d\t%d\n", p->data.goods_id, p->data.goods_name,
                p->data.goods_price, p->data.goods_discount, p->data.goods_amount,
                p->data.goods_remain);
        count++;
    }

    fclose(fp);
    return count;
}
