/**
 * @file workerManager.h
 * @author Bruno Ragucci  - Embedded software engineer
 * @date 12 APR 2025
 * @brief Header for the multi-threaded worker manager module.
 * 
 * This module allows the user to register, manage, and execute worker
 * routines in separate threads based on priority levels.
 * 
 * @copyright
 * Copyright (c) 2025 Bruno Ragucci.  
 * MIT License.
 */

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "linkedListDynamic.h"
#include "workerManager.h"

#define WORKERMANAGER_PRIORITY_NUM             10u

/**
 * @brief Internal thread argument structure passed to each worker thread.
 */
 typedef struct {
    Node_t **workerList;           /**< Pointer to the list of workers for this thread. */
    uint32_t sleepTime;            /**< Sleep duration between worker cycles (in µs). */
    pthread_mutex_t *mutex;        /**< Mutex for thread-safe list access. */
} threadArgs_t;

/**
 * @brief Node structure wrapping thread metadata.
 */
typedef struct {
    struct {
        pthread_t *thread;         /**< Thread handler pointer. */
        threadArgs_t threadArgs;   /**< Arguments passed to the thread. */
    } metadata;
    void *next;                    /**< Next node (if needed in list format). */
} threadNode_t;

/*************** STATIC SECTION ***************/

static volatile uint8_t workerManagerRunning = 0;

static Node_t *_workersList[WORKERMANAGER_PRIORITY_NUM] = { 0 };
static Node_t *_pthreadList[WORKERMANAGER_PRIORITY_NUM] = { 0 };
static pthread_mutex_t _mutexList[WORKERMANAGER_PRIORITY_NUM];

/**
 * @brief Thread routine for managing workers by priority
 */
static void *_workManagerHandler(void *args) {
    threadArgs_t *threadArgs = (threadArgs_t *)args;

    pthread_mutex_t *mutex = threadArgs->mutex;

    if (workerManagerRunning) {
        pthread_mutex_lock(mutex);
        Node_t **workerList = threadArgs->workerList;
        while ((*workerList) != NULL) {
            worker_t *worker = (worker_t *)(*workerList)->item;
            worker_handleInit(worker);
            workerList = (Node_t **)&((*workerList)->next);
        }
        pthread_mutex_unlock(mutex);
    }

    while (workerManagerRunning) {
        pthread_mutex_lock(mutex);
        Node_t **workerList = threadArgs->workerList;
        while ((*workerList) != NULL) {
            worker_t *worker = (worker_t *)(*workerList)->item;
            worker_handleRun(worker);
            workerList = (Node_t **)&((*workerList)->next);
        }
        pthread_mutex_unlock(mutex);
        usleep(threadArgs->sleepTime);
    }

    pthread_mutex_lock(mutex);
    Node_t **workerList = threadArgs->workerList;
    while ((*workerList) != NULL) {
        worker_t *worker = (worker_t *)(*workerList)->item;
        worker_handleEnd(worker);
        workerList = (Node_t **)&((*workerList)->next);
    }
    pthread_mutex_unlock(mutex);

    return NULL;
}

/*************** PUBLIC SECTION ***************/

/**
 * @brief Initialize the worker manager and start priority threads.
 */
void workerManager_init(void) {
    workerManagerRunning = 1;

    for (uint8_t i = 0; i < WORKERMANAGER_PRIORITY_NUM; i++) {
        _workersList[i] = NULL;
        pthread_mutex_init(&_mutexList[i], NULL);

        //_pthreadList[i] = malloc(sizeof(Node_t));
        void *item = malloc(sizeof(threadNode_t));
        _pthreadList[i] = linkedListDynamic_createNode(item);

        threadNode_t *threadNode = (threadNode_t *)_pthreadList[i]->item;
        threadNode->metadata.threadArgs.workerList = &_workersList[i];
        threadNode->metadata.threadArgs.sleepTime = 100000; // 100ms
        threadNode->metadata.threadArgs.mutex = &_mutexList[i];

        threadNode->metadata.thread = malloc(sizeof(pthread_t));
        pthread_create(threadNode->metadata.thread, NULL, _workManagerHandler,
                       (void *)&threadNode->metadata.threadArgs);
    }
}

 /**
  * @brief Add a worker to a given priority level.
  * 
  * @param worker Pointer to the worker definition.
  * @param prio Priority index [0 - N). Lower index = higher priority.
  */
void workerManager_addWorker(worker_t *worker, uint8_t prio) {
    if (prio >= WORKERMANAGER_PRIORITY_NUM) {
        printf("Error: Priority %d exceeds allowed range\n", prio);
        return;
    }

    pthread_mutex_lock(&_mutexList[prio]);

    Node_t **workerList = &_workersList[prio];
    while ((*workerList) != NULL) {
        workerList = (Node_t **)&((*workerList)->next);
    }

    *workerList = malloc(sizeof(Node_t));
    (*workerList)->item = worker;
    (*workerList)->next = NULL;

    pthread_mutex_unlock(&_mutexList[prio]);
}

/**
 * @brief Remove a worker from any priority level.
 * 
 * @param worker Pointer to the worker to remove.
 */
void workerManager_removeWorker(worker_t *worker) {
    for (uint8_t prio = 0; prio < WORKERMANAGER_PRIORITY_NUM; prio++) {
        pthread_mutex_lock(&_mutexList[prio]);
        Node_t **workerList = &_workersList[prio];
        Node_t *prev = NULL;

        while (*workerList != NULL) {
            if ((*workerList)->item == worker) {
                Node_t *toDelete = *workerList;
                if (prev) {
                    prev->next = toDelete->next;
                } else {
                    _workersList[prio] = toDelete->next;
                }
                free(toDelete);
                pthread_mutex_unlock(&_mutexList[prio]);
                return;
            }
            prev = *workerList;
            workerList = (Node_t **)&((*workerList)->next);
        }
        pthread_mutex_unlock(&_mutexList[prio]);
    }
}

/**
 * @brief Stop all worker threads and cleanup resources.
 */
void workerManager_end(void) {
    workerManagerRunning = 0;

    for (uint8_t i = 0; i < WORKERMANAGER_PRIORITY_NUM; i++) {
        threadNode_t *threadNode = (threadNode_t *)_pthreadList[i]->item;
        pthread_join(*(threadNode->metadata.thread), NULL);

        free(threadNode->metadata.thread);
        free(threadNode);
        linkedListDynamic_destroyList(_pthreadList[i]);

        pthread_mutex_destroy(&_mutexList[i]);

        Node_t *node = _workersList[i];
        while (node != NULL) {
            Node_t *next = node->next;
            worker_t *worker = (worker_t *)node->item;
            if (worker->end.handler) {
                worker->end.handler(worker->end.args);
            }
            node = next;
        }

        node = _workersList[i];
        linkedListDynamic_destroyList(node);
    }
}

/**
* @brief Set the sleep time for the specific priority list.
*/
void workerManager_setPriorityListSleepTime(uint8_t prio, uint32_t sleepTime)
{
    if (prio >= WORKERMANAGER_PRIORITY_NUM) {
        printf("Error: Priority %d exceeds allowed range\n", prio);
    }
    else{
        threadNode_t *threadNode = (threadNode_t *)_pthreadList[prio]->item;
        threadNode->metadata.threadArgs.sleepTime = sleepTime;
    }
}
