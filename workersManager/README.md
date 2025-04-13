# workersManager

# Worker Manager Module

A lightweight and modular **worker management system** written in C, designed for embedded or multithreaded applications.  
It provides a flexible interface for defining and executing units of work through structured lifecycle phases: `init`, `run`, and `end`.

---

## 📂 Project Structure

```
├── worker.h              # Worker entity definition and public API
├── worker.c              # Worker implementation
├── workerManager.h       # Worker manager API
├── workerManager.c       # Worker manager logic
```

---

## ⚙️ Features

- Simple API for creating and handling workers
- Thread-based execution model (POSIX)
- Worker lifecycle support: `init`, `run`, `end`
- Per-priority scheduling (configurable)
- Fully Doxygen-documented

---

## 🚀 Getting Started

### 1. Create a Worker

```c
worker_t *myWorker = NULL;
worker_makeWorker("Logger", &myWorker);

myWorker->init.handler = logger_init;
myWorker->run.handler  = logger_run;
myWorker->end.handler  = logger_end;
```

### 2. Add Worker to Manager

```c
workerManager_addWorker(myWorker, 1); // Priority 1
```

### 3. Start the Manager

```c
workerManager_init();
// ... runtime ...
workerManager_end(); // Graceful shutdown
```

---

## 📚 Documentation (Doxygen)

To generate HTML documentation:

```bash
doxygen Doxyfile
```

Minimal `Doxyfile` configuration:

```
PROJECT_NAME = "WorkerManager"
INPUT = ./
RECURSIVE = YES
FILE_PATTERNS = *.c *.h
GENERATE_LATEX = NO
OUTPUT_DIRECTORY = docs
```

Output will be in `docs/html/index.html`.

---

## 🧱 Dependencies

- POSIX Threads (`pthread.h`)
- C Standard Library
- Custom `linkedListDynamic.h`

---

## 📄 License

MIT License  
© 2025 Bruno Ragucci – All rights reserved.

---

## 👨‍💻 Author

**Bruno Ragucci**  
Embedded Software Engineer  
📧 bruno (at) ragucci.it  
