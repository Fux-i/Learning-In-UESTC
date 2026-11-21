#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

GoodsInfo read_goods_info() {
    GoodsInfo item;
    int c;

    read_line(item.goods_id, MAX_ID_LEN);
    read_line(item.goods_name, MAX_NAME_LEN);

    scanf("%d", &item.goods_price);
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    read_line(item.goods_discount, MAX_DISCOUNT_LEN);

    scanf("%d", &item.goods_amount);
    scanf("%d", &item.goods_remain);
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    return item;
}
