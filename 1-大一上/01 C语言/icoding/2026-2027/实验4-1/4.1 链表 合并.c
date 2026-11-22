#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
void lnk_merge(LinkList A, LinkList B, LinkList C) {
    LinkList pa = A->next;
    LinkList pb = B->next;
    LinkList pc = C;

    while (pa != NULL && pb != NULL) {
        pc->next = pa;
        pc = pa;
        pa = pa->next;
        pc->next = pb;
        pc = pb;
        pb = pb->next;
    }
    while (pa != NULL) {
        pc->next = pa;
        pc = pa;
        pa = pa->next;
    }
    while (pb != NULL) {
        pc->next = pb;
        pc = pb;
        pb = pb->next;
    }
    pc->next = NULL;
    A->next = NULL;
    B->next = NULL;
}
