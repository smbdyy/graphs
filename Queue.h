#ifndef QUEUE_H
#define QUEUE_H

#include <malloc.h>
#include <stdbool.h>

struct Node {
    unsigned int value;
    struct Node* next;
};

struct Node* createNode(unsigned int value);
void deleteNode(struct Node* node);

struct Queue {
    struct Node* front;
    struct Node* back;
};

struct Queue* createQueue();
void deleteQueue(struct Queue* queue);
bool enqueue(struct Queue* queue, unsigned int value);
unsigned int dequeue(struct Queue* queue);

#endif
