/**
 * @file workerManager.h
 * @author Bruno Ragucci - Embedded software engineer
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

 #ifndef WORKER_MANAGER_H
 #define WORKER_MANAGER_H
 
 #include <stdint.h>

  #include "worker.h"
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 /**
  * @brief Initialize the worker manager and start priority threads.
  */
 void workerManager_init(void);
 
 /**
  * @brief Add a worker to a given priority level.
  * 
  * @param worker Pointer to the worker definition.
  * @param prio Priority index [0 - N). Lower index = higher priority.
  */
 void workerManager_addWorker(worker_t *worker, uint8_t prio);
 
 /**
  * @brief Remove a worker from any priority level.
  * 
  * @param worker Pointer to the worker to remove.
  */
 void workerManager_removeWorker(worker_t *worker);
 
 /**
  * @brief Stop all worker threads and cleanup resources.
  */
 void workerManager_end(void);
 
 /**
  * @brief [Optional] Start a single worker manually (future expansion).
  * 
  * @param worker Worker to start.
  */
 void workerManager_startWorker(worker_t *worker);
 
 /**
  * @brief [Optional] Stop a single worker manually (future expansion).
  * 
  * @param worker Worker to stop.
  */
 void workerManager_stopWorker(worker_t *worker);

 /**
  * @brief Set the sleep time for the specific priority list.
  * 
  * @param prio Priority index [0 - N).
  * @param sleepTime time in usec that the task sleeping every cycle.
  */
  void workerManager_setPriorityListSleepTime(uint8_t prio, uint32_t sleepTime);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // WORKER_MANAGER_H
 