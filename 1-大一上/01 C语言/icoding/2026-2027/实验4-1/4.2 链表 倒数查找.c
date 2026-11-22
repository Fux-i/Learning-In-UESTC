#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
int lnk_search(LinkList L, int k, ElemType *p_ele) {
    LinkList fast = L->next;
    LinkList slow = L->next;
    int i;

    if (k <= 0 || fast == NULL) {
        return 0;
    }

    for (i = 0; i < k; i++) {
        if (fast == NULL) {
            return 0;
        }
        fast = fast->next;
    }

    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    *p_ele = slow->data;
    return 1;
}
