#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

extern int CurrentCnt;

bool insert_item(GoodsList *L, GoodsInfo goodsInfo, int choice) {
    GoodsList *node;
    GoodsList *p;
    int i;

    node = (GoodsList *)malloc(sizeof(GoodsList));
    if (node == NULL) {
        return false;
    }
    node->data = goodsInfo;
    node->next = NULL;

    if (choice == 1) {
        node->next = L->next;
        L->next = node;
        CurrentCnt++;
        return true;
    }

    if (choice == 0) {
        p = L;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = node;
        CurrentCnt++;
        return true;
    }

    if (choice > 1) {
        p = L;
        for (i = 1; i < choice && p->next != NULL; i++) {
            p = p->next;
        }
        if (i != choice) {
            free(node);
            return false;
        }
        node->next = p->next;
        p->next = node;
        CurrentCnt++;
        return true;
    }

    free(node);
    return false;
}
