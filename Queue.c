#include "Queue.h"

struct Queue* createQueue() {
    struct Queue* q = (struct Queue* )malloc(sizeof(struct Queue));
    return q;
}

void enqueue(struct Queue* queue, unsigned int value) {
    struct Node* node = (struct Node* )malloc(sizeof(struct Node));
    node->value = value;

    node->next = queue->front;
    queue->front = node;
}

unsigned int dequeue(struct Queue* queue) {
    if (queue->front == NULL) return 0;

    struct Node* frontNode = queue->front;
    unsigned int value = frontNode->value;
    queue->front = queue->front->next;
    free(frontNode);

    return value;
}