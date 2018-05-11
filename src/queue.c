/**
 * C collection Queue: queue.c
 *
 * Copyright (c) 2018 Junsulime
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include "queue.h"

static int initialized = FALSE;
static QueueOp operator;

QueueOp queueOp() {
    if (!initialized) {
        operator.init = queueInit;
        operator.free = queueFree;
        operator.contain = queueContain;
        operator.isEmpty = queueIsEmpty;
        operator.iterator = queueIterator;
        operator.hasNext = queueHasNext;
        operator.next = queueNext;
        operator.enqueue = queueEnqueue;
        operator.dequeue = queueDequeue;
        operator.length = queueLength;

        initialized = TRUE;
    }
    return operator;
}

void queueInit(Queue *queue) {
    queue->head = (struct _Node*) malloc(sizeof(struct _Node));
    queue->tail = queue->head;
    queue->length = 0;
}

void queueFree(Queue *queue) { 
    struct _Node *current = queue->head;
    struct _Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int queueContain(Queue *queue, int e) {
    struct _Node *current = queue->head->next;

    while (current != NULL) {
        if (current->item == e) {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

int queueIsEmpty(Queue *queue) {
    return queue->head == queue->tail;
}

QueueIter* queueIterator(Queue *queue) {
    QueueIter *iterator = (QueueIter*) malloc(sizeof(QueueIter));
    iterator->_queue = queue;
    iterator->current = queue->head->next;
    
    return iterator;
}

int queueHasNext(QueueIter *iterator) {
    return iterator->current != NULL;
}

int queueNext(QueueIter *iterator) {
    int item = iterator->current->item;
    iterator->current = iterator->current->next;
    return item;
}

void queueEnqueue(Queue *queue, int e) {
    struct _Node *newNode = (struct _Node*) malloc(sizeof(struct _Node));
    newNode->next = NULL;
    newNode->item = e;

    queue->tail->next = newNode;
    queue->tail = newNode;
    queue->length++;
}

int queueDequeue(Queue *queue) {
    struct _Node *first = queue->head->next;
    queue->head->next = first->next;
    if (first == queue->tail) {
        queue->tail = queue->head;
    }

    int item = first->item;
    free(first);

    queue->length--;
    return item;
}

int queueLength(Queue *queue) {
    return queue->length;
}


