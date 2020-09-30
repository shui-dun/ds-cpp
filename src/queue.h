#pragma once

typedef void *QueueType;

typedef struct QNode {
	struct QNode *next;
	QueueType data;
}QNode;

typedef struct {
	QNode *front;
	QNode *rear;
}LinkQueue;

LinkQueue *lqueue_init();

int lqueue_offer(LinkQueue *queue, QueueType data);

int lqueue_poll(LinkQueue *queue, QueueType *data);

int lqueue_peek(LinkQueue *queue, QueueType *data);

int lqueue_len(LinkQueue *queue);

int lqueue_empty(LinkQueue *queue);

void lqueue_print(LinkQueue *queue);

void lqueue_destroy(LinkQueue **queue);

typedef struct {
	int *base;
	int front;
	int rear;
	int len;
	int capacity;
}SqQueue;

SqQueue *squeue_init(int size);

int squeue_offer(SqQueue *queue, int data);

int squeue_poll(SqQueue *queue, int *data);

void squeue_print(SqQueue *queue);