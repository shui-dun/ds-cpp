#pragma once

typedef int ListType;

typedef struct {
	ListType *data;
	int len;
	int capacity;
}SqList;

SqList *sqlist_init(int size);

int sqlist_insert(SqList *sqlist, int pos, ListType data);

void sqlist_print(SqList *sqlist);

int sqlist_delete(SqList *sqlist, int pos, ListType *data);

typedef struct LNode {
	ListType data;
	struct LNode *next;
}LNode, *LinkedList;

LinkedList list_init();

LinkedList list_create(ListType *data, int len);

int list_find(LinkedList list, int pos, ListType *data);

int list_insert(LinkedList list, int pos, ListType data);

void list_print(LinkedList list);

LinkedList list_reverse(LinkedList head);

int list_delete(LinkedList list, int pos, ListType *data);

void list_destroy(LNode **list);

void list_merge_sort(LNode *head);

void list_insert_sort(LNode *head);

typedef struct CLNode {
	ListType data;
	struct CLNode *next;
}CLNode, *CList;

void clist_print(CList clist);

int clist_len(CList clist);

CLNode *clist_find(CList list, int pos);

int clist_insert(CList *tail, int pos, ListType data);

int clist_delete(CList *tail, int pos, ListType *data);

int clist_rem_next(CLNode **tail, CLNode **node, ListType *data);

typedef struct DLNode {
	ListType data;
	struct DLNode *next;
	struct DLNode *pre;
}DLNode, *DList;

DList dlist_init();

void dlist_print(DList dlist);

int dlist_find(DList dlist, int pos, ListType *data);

int dlist_insert(DList dlist, int pos, ListType data);

int dlist_delete(DList dlist, int pos, ListType *data);