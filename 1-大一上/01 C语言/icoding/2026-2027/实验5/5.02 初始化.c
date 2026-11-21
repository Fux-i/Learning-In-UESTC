#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

void init_list(GoodsList **pL) {
    FILE *fp;
    GoodsList *head;
    GoodsList *tail;
    GoodsList *node;

    head = (GoodsList *)malloc(sizeof(GoodsList));
    if (head == NULL) {
        *pL = NULL;
        return;
    }
    head->next = NULL;
    *pL = head;
    tail = head;

    fp = fopen(GOODS_FILE_NAME, "r");
    if (fp == NULL) {
        return;
    }

    for (;;) {
        node = (GoodsList *)malloc(sizeof(GoodsList));
        if (node == NULL) {
            break;
        }
        if (fscanf(fp, "%s %s %d %s %d %d", node->data.goods_id, node->data.goods_name,
                   &node->data.goods_price, node->data.goods_discount, &node->data.goods_amount,
                   &node->data.goods_remain) != 6) {
            free(node);
            break;
        }
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

    fclose(fp);
}
