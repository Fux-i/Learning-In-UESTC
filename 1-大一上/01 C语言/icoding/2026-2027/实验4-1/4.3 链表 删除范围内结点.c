#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
void lnk_del_x2y(LinkList L, ElemType mink, ElemType maxk) {
    LinkList p = L;
    LinkList q;

    while (p->next != NULL) {
        if (p->next->data > mink && p->next->data < maxk) {
            q = p->next;
            p->next = q->next;
            free(q);
        } else {
            p = p->next;
        }
    }
}
