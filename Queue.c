#include "Queue.h"

struct Node* createNode(unsigned int value) {
    struct Node* node = (struct Node* )malloc(sizeof(struct Node));
    if (node == NULL) return node;

    node->value = value;
    node->next = NULL;

    return node;
}

void deleteNode(struct Node* node) {
    if (node == NULL) return;
    if (node->next != NULL) deleteNode(node->next);

    free(node);
}

struct Queue* createQueue() {
    struct Queue* q = (struct Queue* )malloc(sizeof(struct Queue));
    if (q == NULL) return q;

    q->front = NULL;
    q->back = NULL;

    return q;
}

void deleteQueue(struct Queue* queue) {
    if (queue == NULL) return;
    deleteNode(queue->front);
    free(queue);
}

bool enqueue(struct Queue* queue, unsigned int value) {
    struct Node* node = createNode(value);
    if (node == NULL) return false;

    if (queue->front == NULL) {
        queue->front = node;
    }
    else if (queue->back == NULL) {
        queue->back = node;
        queue->front->next = node;
    }
    else {
        queue->back->next = node;
        queue->back = node;
    }

    return true;
}

unsigned int dequeue(struct Queue* queue) {
    if (queue->front == NULL) return 0;

    struct Node* frontNode = queue->front;
    unsigned int value = frontNode->value;
    queue->front = queue->front->next;
    free(frontNode);

    return value;
}