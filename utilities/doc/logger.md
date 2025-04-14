# Logger Module (MISRA C:2012 Compliant)

A lightweight, modular, and **MISRA C:2012-compliant** logging utility written in C. Designed for embedded systems and safety-critical applications, this logger provides customizable output, optional thread safety, and support for multiple log levels.

---

## 📂 Files

- `logger.c`: Implementation of the logging module.
- `logger.h`: Public API for users of the logger.

---

## ✨ Features

- 🧩 Pluggable output via user-defined callbacks.
- 🧵 Optional thread safety using POSIX `pthread_mutex`.
- 📄 Built-in file output (e.g., to `stdout`, `stderr`, or log files).
- 🪵 Support for log levels: `DEBUG`, `INFO`, `WARN`, and `ERROR`.
- 🛡️ Clean and MISRA C:2012 compliant.

---

## 🧰 API Overview

### Logger Levels

```c
typedef enum {
    LOGGER_LEVEL_DEBUG = 0,
    LOGGER_LEVEL_INFO,
    LOGGER_LEVEL_WARN,
    LOGGER_LEVEL_ERROR,
    LOGGER_LEVEL_MAX
} LoggerLevel;
```

---

### Logger Callback Type

```c
typedef void (*LoggerCallback)(
    LoggerLevel level,
    const char *timestamp,
    const char *message
);
```

---

### Initialization

```c
void logger_initialize(LoggerCallback callback);
```

Initializes the logger with a custom callback. You can use the built-in `logger_file_output` for file logging.

---

### Enable/Disable Thread Safety

```c
void logger_enable_thread_safety(int enable);
```

Set to `1` to enable mutex-based thread safety, `0` to disable (default is enabled).

---

### Set Output File

```c
void logger_set_log_file_pointer(void *file);
```

Sets a `FILE*` to be used by the built-in file logger.

Example:

```c
FILE *log_file = fopen("log.txt", "w");
logger_set_log_file_pointer(log_file);
```

---

### Log a Message

```c
void logger_log_message(LoggerLevel level, const char *message, const char *timestamp);
```

Logs a message through the current callback. `timestamp` can be `NULL`.

Example:

```c
logger_log_message(LOGGER_LEVEL_INFO, "System initialized", "2025-04-12 10:00:00");
```

---

### Built-in File Output Function

```c
void logger_file_output(LoggerLevel level, const char *timestamp, const char *message);
```

A default callback that writes logs to a file. Call `logger_initialize(logger_file_output)` to use it.

---

## 🧪 Sample Output

```
[2025-04-12 10:00:00] [INFO] System initialized
[2025-04-12 10:01:12] [ERROR] Failed to read sensor data
```

---

## 🛠️ Example Usage

```c
#include "logger.h"
#include <stdio.h>

int main(void)
{
    logger_initialize(logger_file_output);
    logger_set_log_file_pointer(stdout);

    logger_log_message(LOGGER_LEVEL_INFO, "Logger started", "2025-04-12 10:00:00");

    return 0;
}
```

---

## 🔐 License

MIT License  
© 2025 Bruno Ragucci — All rights reserved.

---

## 👤 Author

**Bruno Ragucci**  
Embedded Software Engineer  
📧 bruno (at) ragucci.it
