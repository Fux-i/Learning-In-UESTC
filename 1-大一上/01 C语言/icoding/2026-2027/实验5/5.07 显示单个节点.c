#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

void output_one_item(GoodsList *p) {
    if (p == NULL) {
        return;
    }
    printf("%s\t%s\t%d\t%s\t%d\t%d\n", p->data.goods_id, p->data.goods_name, p->data.goods_price,
           p->data.goods_discount, p->data.goods_amount, p->data.goods_remain);
}
