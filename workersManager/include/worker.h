/**
 *  \file worker.h
 *	
 *  \author Bruno Ragucci - Embedded Software Engineer
 *  \n mail : bruno (at) ragucci.it
 *	
 *  \date 10 APR 2025
 *	
 *  \brief Worker structure and lifecycle management functions.
 *  
 *  \details
 *  This module defines a generic worker structure capable of managing
 *  lifecycle phases: initialization, execution, and termination.
 *  It also provides utilities to create, destroy, and handle these workers.
 *	
 *  \copyright
 *  Copyright (c) 2025 by Bruno Ragucci - All rights reserved.
 *  \n
 *  \license MIT
 */

 #ifndef __WORKER_H__
 #define __WORKER_H__
 
 #include <stdint.h>
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 /**
  * @def WORKER_NAME_MAX_LEN
  * @brief Maximum length of the worker name (including null terminator).
  */
 #define WORKER_NAME_MAX_LEN 64
 
 /**
  * @def WORKER_STATUS_IDLE
  * @brief Status constant indicating the worker is idle.
  */
 #define WORKER_STATUS_IDLE         0u
 
 /**
  * @def WORKER_STATUS_ACTIVE
  * @brief Status constant indicating the worker is active.
  */
 #define WORKER_STATUS_ACTIVE       1u
 
 /**
  * @brief Structure representing a worker with metadata and function handlers.
  *
  * A worker is an executable unit that may define three optional phases:
  * `init`, `run`, and `end`, each with its own function pointer and arguments.
  */
 typedef struct {
     /**
      * @brief Metadata associated with the worker.
      */
     struct {
         char name[WORKER_NAME_MAX_LEN]; /**< Worker name identifier. */
         uint8_t status;                 /**< Worker execution status. */
     } metadata;
 
     /**
      * @brief Initialization function and its argument.
      */
     struct {
         void (*handler)(void *args);    /**< Pointer to init function. */
         void *args;                     /**< Argument for init function. */
     } init;
 
     /**
      * @brief Execution function and its argument.
      */
     struct {
         void (*handler)(void *args);    /**< Pointer to run function. */
         void *args;                     /**< Argument for run function. */
     } run;
 
     /**
      * @brief Termination function and its argument.
      */
     struct {
         void (*handler)(void *args);    /**< Pointer to end function. */
         void *args;                     /**< Argument for end function. */
     } end;
 
 } worker_t;
 
 /**
  * @brief Creates a new worker instance and initializes it with a name.
  *
  * @param name Null-terminated string to name the worker.
  * @param worker Pointer to a pointer that will receive the allocated worker.
  */
 void worker_makeWorker(char *name, worker_t **worker);
 
 /**
  * @brief Destroys the given worker and frees associated memory.
  *
  * @param worker Pointer to the worker to be destroyed.
  */
 void worker_destroyWorker(worker_t *worker);
 
 /**
  * @brief Executes the worker's initialization phase if defined.
  *
  * @param worker Pointer to the worker.
  */
 void worker_handleInit(worker_t *worker);
 
 /**
  * @brief Executes the worker's run phase if defined.
  *
  * @param worker Pointer to the worker.
  */
 void worker_handleRun(worker_t *worker);
 
 /**
  * @brief Executes the worker's end phase if defined.
  *
  * @param worker Pointer to the worker.
  */
 void worker_handleEnd(worker_t *worker);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // __WORKER_H__
 