#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

LinkQueue* lqueue_init() {
    LinkQueue* lqueue = (LinkQueue*)malloc(sizeof(LinkQueue));
    lqueue->front = (QNode*)malloc(sizeof(QNode));
    lqueue->front->next = NULL;
    lqueue->rear = lqueue->front;
    return lqueue;
}

int lqueue_offer(LinkQueue* queue, QueueType data) {
    QNode* node = (QNode*)malloc(sizeof(QNode));
    if (!node)
        return 0;
    node->data = data;
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    return 1;
}

int lqueue_poll(LinkQueue* queue, QueueType* data) {
    if (queue->front == queue->rear)
        return 0;
    QNode* node = queue->front->next;
    queue->front->next = node->next;
    if (node == queue->rear)
        queue->rear = queue->front;
    if (data)
        *data = node->data;
    free(node);
    return 1;
}

int lqueue_peek(LinkQueue* queue, QueueType* data) {
    if (queue->front == queue->rear)
        return 0;
    *data = queue->front->next->data;
    return 1;
}

int lqueue_len(LinkQueue* queue) {
    int len = 0;
    QNode* node = queue->front->next;
    while (node) {
        len++;
        node = node->next;
    }
    return len;
}

int lqueue_empty(LinkQueue* queue) {
    return lqueue_len(queue) == 0;
}

void lqueue_print(LinkQueue* queue) {
    QNode* node = queue->front->next;
    while (node) {
        if (node->data)
            printf("%c ", *(char*)(node->data));
        node = node->next;
    }
    putchar('\n');
}

void lqueue_destroy(LinkQueue** ptr) {
    LinkQueue* queue = *ptr;
    QNode* node = queue->front;
    QNode* pre = node;
    while (node) {
        node = node->next;
        free(pre);
        pre = node;
    }
    free(queue);
    *ptr = NULL;
}

SqQueue* squeue_init(int size) {
    SqQueue* queue = (SqQueue*)malloc(sizeof(SqQueue));
    queue->base = (int*)malloc(sizeof(int) * size);
    queue->capacity = size;
    queue->front = 0;
    queue->rear = 0;
    queue->len = 0;
    return queue;
}

int squeue_offer(SqQueue* queue, int data) {
    if (queue->len == queue->capacity)
        return 0;
    queue->base[queue->front] = data;
    queue->front = (queue->front + 1) % queue->capacity;
    queue->len++;
    return 1;
}

int squeue_poll(SqQueue* queue, int* data) {
    if (queue->len == 0)
        return 0;
    *data = queue->base[queue->rear];
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->len--;
    return 1;
}

void squeue_print(SqQueue* queue) {
    int i = queue->rear;
    while (i != queue->front) {
        printf("%d ", queue->base[i]);
        i = (i + 1) % queue->capacity;
    }
    putchar('\n');
}
