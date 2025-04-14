/**
 *  \file logger.h
 *  
 *  \author Bruno Ragucci - Embedded Software Engineer
 *  \n mail : bruno (at) ragucci.it
 *  
 *  \date 13 APR 2025
 *  
 *  @brief MISRA C:2012 compliant logger API.
 *
 *  \copyright Copyright (c) 2025 by Bruno Ragucci - All rights reserved.
 *  \n
 *  \license MIT
 */

 #ifndef LOGGER_H
 #define LOGGER_H
 
 #include <stddef.h>
 
 /**
  * @brief Log levels.
  */
 typedef enum {
     LOGGER_LEVEL_DEBUG = 0,
     LOGGER_LEVEL_INFO,
     LOGGER_LEVEL_WARN,
     LOGGER_LEVEL_ERROR,
     LOGGER_LEVEL_MAX
 } LoggerLevel;
 
 /**
  * @brief Logger callback function type.
  *
  * @param level Log level.
  * @param timestamp Optional string timestamp (may be NULL).
  * @param message Message string.
  */
 typedef void (*LoggerCallback)(LoggerLevel level, const char *timestamp, const char *message);
 
 /**
  * @brief Initializes the logger.
  *
  * @param callback Callback function for log output.
  */
 void logger_initialize(LoggerCallback callback);
 
 /**
  * @brief Enables or disables thread safety.
  *
  * @param enable 0 = disabled, 1 = enabled
  */
 void logger_enable_thread_safety(int enable);
 
 /**
  * @brief Logs a message.
  *
  * @param level Log level.
  * @param message Message string.
  * @param timestamp Optional timestamp string, or NULL.
  */
 void logger_log_message(LoggerLevel level, const char *message, const char *timestamp);
 
 /**
  * @brief Sets a file stream for the built-in file logger.
  *
  * @param file File pointer (e.g., stdout, stderr, or custom log file).
  */
 void logger_set_log_file_pointer(void *file);
 
 /**
  * @brief File logging callback.
  */
 void logger_file_output(LoggerLevel level, const char *timestamp, const char *message);
 
 #endif /* LOGGER_H */
 