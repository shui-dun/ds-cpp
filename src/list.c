#include <stdlib.h>
#include <stdio.h>
#include "list.h"

SqList* sqlist_init(int size) {
    SqList* sqlist = (SqList*)malloc(sizeof(SqList));
    sqlist->data = malloc(sizeof(ListType) * size);
    sqlist->len = 0;
    sqlist->capacity = size;
    return sqlist;
}

int sqlist_insert(SqList* sqlist, int pos, ListType data) {
    if (pos < 0 || pos > sqlist->len)
        return 0;
    if (sqlist->len == sqlist->capacity) {
        if ((sqlist->data = (ListType*)realloc(sqlist->data, sizeof(ListType) * sqlist->capacity * 2)) == NULL)
            return -1;
        sqlist->capacity *= 2;
    }
    for (int i = sqlist->len; i >= pos; i--)
        sqlist->data[i + 1] = sqlist->data[i];
    sqlist->data[pos] = data;
    sqlist->len++;
    return 1;
}

void sqlist_print(SqList* sqlist) {
    for (int i = 0; i < sqlist->len; i++)
        printf("%d ", (sqlist->data[i]));
    putchar('\n');
}

int sqlist_delete(SqList* sqlist, int pos, ListType* data) {
    if (pos < 0 || pos > sqlist->len - 1)
        return 0;
    *data = sqlist->data[pos];
    for (int i = pos; i < sqlist->len - 1; i++)
        sqlist->data[i] = sqlist->data[i + 1];
    sqlist->len--;
    return 1;
}

LinkedList list_init() {
    LinkedList list = (LinkedList)malloc(sizeof(LNode));
    list->next = NULL;
    return list;
}

LinkedList list_create(ListType* data, int len) {
    LinkedList head = (LinkedList)malloc(sizeof(LNode));
    LNode* cur = head;
    for (int i = 0; i < len; i++) {
        LNode* node = (LNode*)malloc(sizeof(LNode));
        node->data = data[i];
        cur->next = node;
        cur = node;
    }
    cur->next = NULL;
    return head;
}

int list_find(LinkedList list, int pos, ListType* data) {
    for (int i = 0; i <= pos; i++) {
        list = list->next;
        if (!list)
            return 0;
    }
    *data = list->data;
    return 1;
}

int list_insert(LinkedList list, int pos, ListType data) {
    for (int i = 0; i < pos; i++) {
        list = list->next;
        if (!list)
            return 0;
    }
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->data = data;
    node->next = list->next;
    list->next = node;
    return 1;
}

void list_print(LinkedList list) {
    if (!list) return;
    list = list->next;
    while (list) {
        printf("%d ", (list->data));
        list = list->next;
    }
    putchar('\n');
}

LinkedList list_reverse(LinkedList head) {
    if (!head || !head->next) return head;
    LNode* pre = NULL, * cur = head->next, * next = NULL, * last = head;
    while (last->next)
        last = last->next;
    head->next = last;
    while (cur) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return head;
}

int list_delete(LinkedList list, int pos, ListType* data) {
    for (int i = 0; i < pos; i++) {
        list = list->next;
        if (!list)
            return 0;
    }
    *data = list->next->data;
    LNode* node = list->next;
    list->next = list->next->next;
    free(node);
    return 1;
}

void list_destroy(LNode** list) {
    LNode* cur = *list, * temp = *list;
    while (cur) {
        temp = temp->next;
        free(cur);
        cur = temp;
    }
    *list = NULL;
}

static LNode* list_split(LNode* list) {
    if (!list || !list->next)
        return list;
    LNode* slow = list, * fast = list->next, * tail = NULL;
    while (fast) {
        fast = fast->next;
        if (fast) fast = fast->next;
        else break;
        slow = slow->next;
    }
    tail = slow;
    slow = slow->next;
    tail->next = NULL;
    return slow;
}

static LNode* merge_list(LNode* head1, LNode* head2) {
    if (!head1) return head2;
    if (!head2) return head1;
    LNode node, * cur = &node;
    while (head1 && head2) {
        if (head1->data < head2->data) {
            cur->next = head1;
            head1 = head1->next;
        } else {
            cur->next = head2;
            head2 = head2->next;
        }
        cur = cur->next;
    }
    if (head1)
        cur->next = head1;
    else if (head2)
        cur->next = head2;
    return node.next;
}

static LNode* list_msort(LNode* list) {
    if (!list || !list->next)
        return list;
    LNode* head1 = list;
    LNode* head2 = list_split(list);
    head1 = list_msort(head1);
    head2 = list_msort(head2);
    return merge_list(head1, head2);
}

void list_merge_sort(LNode* head) {
    head->next = list_msort(head->next);
}

void list_insert_sort(LNode* head) {
    if (!head || !head->next || !head->next->next)
        return;
    for (LNode* node1 = head->next; node1->next;) {
        for (LNode* node2 = head; ; node2 = node2->next) {
            if (node1->next->data < node2->next->data) {
                LNode* temp = node1->next->next;
                node1->next->next = node2->next;
                node2->next = node1->next;
                node1->next = temp;
                break;
            }
            if (node2->next == node1) {
                node1 = node1->next;
                break;
            }
        }
    }
}

void clist_print(CList clist) {
    if (!clist)
        return;
    else {
        CLNode* head = clist->next;
        clist = head;
        do {
            printf("%d ", (clist->data));
            clist = clist->next;
        } while (clist != head);
        putchar('\n');
    }
}

int clist_len(CList clist) {
    if (!clist)
        return 0;
    else {
        CLNode* head = clist->next;
        clist = head;
        int len = 0;
        do {
            clist = clist->next;
            len++;
        } while (clist != head);
        return len;
    }
}

CLNode* clist_find(CList list, int pos) {
    CLNode* node = list;
    do {
        node = node->next;
        if (!pos)
            return node;
        pos--;
    } while (node != list);
    return NULL;
}

int clist_insert(CList* tail, int pos, ListType data) {
    CList clist = *tail;
    int len = clist_len(clist);
    if (pos < 0 || pos > len)
        return 0;
    CList rear = (CList)malloc(sizeof(CLNode));
    rear->data = data;
    if (len == 0) {
        rear->next = rear;
        *tail = rear;
    } else if (len == pos) {
        rear->next = clist->next;
        clist->next = rear;
        *tail = rear;
    } else {
        CLNode* node = clist;
        for (int i = 0; i < pos; i++)
            node = node->next;
        rear->next = node->next;
        node->next = rear;
    }
    return 1;
}

int clist_delete(CList* tail, int pos, ListType* data) {
    int len = clist_len(*tail);
    if (pos < 0 || pos >= len || len == 0)
        return 0;
    if (len == 1) {
        *data = (*tail)->data;
        free(*tail);
        *tail = NULL;
    } else if (pos == len - 1) {
        CLNode* rear = *tail;
        while (rear->next != *tail)
            rear = rear->next;
        rear->next = rear->next->next;
        *data = (*tail)->data;
        free(*tail);
        *tail = rear;
    } else {
        CLNode* node = *tail;
        for (int i = 0; i < pos; i++)
            node = node->next;
        CLNode* remove = node->next;
        node->next = node->next->next;
        *data = remove->data;
        free(remove);
    }
    return 1;
}

int clist_rem_next(CLNode** tail, CLNode** pre, ListType* data) {
    CLNode* node = *pre;
    if (!node)
        return 0;
    if (node->next == node) {
        *pre = NULL;
        *data = node->data;
        return -1;
    }
    CLNode* rem = node->next;
    node->next = rem->next;
    *data = rem->data;
    if (rem == *tail)
        *tail = node;
    free(rem);
    return 1;
}

DList dlist_init() {
    DList dlist = (DList)malloc(sizeof(DLNode));
    dlist->next = NULL;
    dlist->pre = NULL;
    return dlist;
}

void dlist_print(DList dlist) {
    if (!dlist) return;
    dlist = dlist->next;
    while (dlist) {
        printf("%d ", (dlist->data));
        dlist = dlist->next;
    }
    putchar('\n');
}

int dlist_find(DList dlist, int pos, ListType* data) {
    for (int i = 0; i <= pos; i++) {
        if (!dlist)
            return 0;
        dlist = dlist->next;
    }
    *data = dlist->data;
    return 1;
}

int dlist_insert(DList dlist, int pos, ListType data) {
    for (int i = 0; i < pos; i++) {
        dlist = dlist->next;
        if (!dlist)
            return 0;
    }
    DList node = (DList)malloc(sizeof(DLNode));
    if (!node) return 0;
    node->data = data;
    node->next = dlist->next;
    node->pre = dlist;
    dlist->next = node;
    if (node->next)
        node->next->pre = node;
    return 1;
}

int dlist_delete(DList dlist, int pos, ListType* data) {
    for (int i = 0; i < pos; i++) {
        if (!dlist)
            return 0;
        dlist = dlist->next;
    }
    DList node = dlist->next;
    dlist->next = node->next;
    if (node->next)
        node->next->pre = dlist;
    *data = node->data;
    free(node);
    return 1;
}
