/**
 *  \file worker.c
 *	
 *  \author Bruno Ragucci - Embedded Software Engineer
 *  \n mail : bruno (at) ragucci.it
 *	
 *  \date 12 APR 2025
 *	
 *  \brief Worker entity management and handler dispatchers.
 *
 *  Provides creation, destruction, and lifecycle control for worker_t entities.
 *
 *  \copyright
 *  Copyright (c) 2025 by Bruno Ragucci - All rights reserved.
 *  \n
 *  \license MIT
 */

 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 
 #include "worker.h"
 
 #define WORKER_NAME_MAX_LEN 64  /**< Maximum allowed worker name length */
  
 /**
  * @brief Creates and initializes a new worker object.
  *
  * @param name A null-terminated string used as the worker's name.
  * @param worker Pointer to a pointer that will be assigned the allocated worker.
  */
 void worker_makeWorker(char *name, worker_t **worker)
 {
     if (!name || !worker) 
        return;
 
     (*worker) = malloc(sizeof(worker_t));
     if (!(*worker)) return;
 
     memset(*worker, 0x00, sizeof(worker_t));
     strncpy((*worker)->metadata.name, name, WORKER_NAME_MAX_LEN - 1);
     (*worker)->metadata.name[WORKER_NAME_MAX_LEN - 1] = '\0';
 }
 
 /**
  * @brief Destroys a worker object and frees its memory.
  *
  * @param worker Pointer to the worker to destroy.
  */
 void worker_destroyWorker(worker_t *worker)
 {
     if (!worker) 
        return;
 
     printf("destroy %s\n", worker->metadata.name);
     free(worker);
 }
 
 /**
  * @brief Calls the init handler of the given worker.
  *
  * @param worker Pointer to the worker.
  */
 void worker_handleInit(worker_t *worker)
 {
     if (worker && worker->init.handler)
         worker->init.handler(worker->init.args);
 }
 
 /**
  * @brief Calls the run handler of the given worker.
  *
  * @param worker Pointer to the worker.
  */
 void worker_handleRun(worker_t *worker)
 {
     if (worker && worker->run.handler)
         worker->run.handler(worker->run.args);
 }
 
 /**
  * @brief Calls the end handler of the given worker.
  *
  * @param worker Pointer to the worker.
  */
 void worker_handleEnd(worker_t *worker)
 {
     if (worker && worker->end.handler)
         worker->end.handler(worker->end.args);
 }
 