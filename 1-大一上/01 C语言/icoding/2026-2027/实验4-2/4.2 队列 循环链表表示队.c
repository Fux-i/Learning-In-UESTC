#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
bool init_queue(LinkQueue *LQ) {
    LinkQueueNode *head = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (head == NULL) {
        return false;
    }
    head->next = head;
    *LQ = head;
    return true;
}
bool enter_queue(LinkQueue *LQ, ElemType x) {
    LinkQueueNode *node = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (node == NULL) {
        return false;
    }
    node->data = x;
    node->next = (*LQ)->next;
    (*LQ)->next = node;
    *LQ = node;
    return true;
}
bool leave_queue(LinkQueue *LQ, ElemType *x) {
    LinkQueueNode *head = (*LQ)->next;
    LinkQueueNode *first = head->next;

    if (first == head) {
        return false;
    }

    *x = first->data;
    head->next = first->next;

    if (first == *LQ) {
        *LQ = head;
    }

    free(first);
    return true;
}
