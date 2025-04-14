/**
 *  \file logger.c
 *  
 *  \author Bruno Ragucci - Embedded Software Engineer
 *  \n mail : bruno (at) ragucci.it
 *  
 *  \date 13 APR 2025
 *  
 *  @brief MISRA C:2012 compliant logger implementation.
 *
 *  \copyright Copyright (c) 2025 by Bruno Ragucci - All rights reserved.
 *  \n
 *  \license MIT
 */

 #include "logger.h"
 #include <stdio.h>
 #include <string.h>
 #include <pthread.h>
 
 #define LOGGER_LEVEL_COUNT ((int)LOGGER_LEVEL_MAX)
 
 static LoggerCallback logger_callback_function = (LoggerCallback)0;
 static int logger_use_thread_safety = 1;
 static pthread_mutex_t logger_mutex = PTHREAD_MUTEX_INITIALIZER;
 static FILE *logger_output_file = (FILE *)0;
 
 void logger_initialize(LoggerCallback callback)
 {
     logger_callback_function = callback;
 }
 
 void logger_enable_thread_safety(int enable)
 {
     logger_use_thread_safety = enable;
 }
 
 void logger_set_log_file_pointer(void *file)
 {
     logger_output_file = (FILE *)file;
 }
 
 void logger_log_message(LoggerLevel level, const char *message, const char *timestamp)
 {
     if ((level >= LOGGER_LEVEL_MAX) || (message == (const char *)0)) {
         return;
     }
 
     if (logger_use_thread_safety != 0) {
         (void)pthread_mutex_lock(&logger_mutex);
     }
 
     if (logger_callback_function != (LoggerCallback)0) {
         logger_callback_function(level, timestamp, message);
     }
 
     if (logger_use_thread_safety != 0) {
         (void)pthread_mutex_unlock(&logger_mutex);
     }
 }
 
 void logger_file_output(LoggerLevel level, const char *timestamp, const char *message)
 {
     const char *level_names[LOGGER_LEVEL_COUNT] = {
         "DEBUG", "INFO", "WARN", "ERROR"
     };
 
     if ((level >= LOGGER_LEVEL_MAX) || (message == (const char *)0)) {
         return;
     }
 
     if (logger_output_file == (FILE *)0) {
         logger_output_file = stdout;
     }
 
     if (timestamp != (const char *)0) {
         (void)fprintf(logger_output_file, "[%s] [%s] %s\n", timestamp, level_names[level], message);
     } else {
         (void)fprintf(logger_output_file, "[%s] %s\n", level_names[level], message);
     }
 
     (void)fflush(logger_output_file);
 }
 