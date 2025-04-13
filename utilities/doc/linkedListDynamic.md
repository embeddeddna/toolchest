# Dynamic Linked List in C

A simple, generic dynamic linked list implementation in C for managing collections of items via pointers.

## 📁 File Structure

- `linkedListDynamic.c` – Core implementation of the dynamic linked list.
- `linkedListDynamic.h` – Header file containing type definitions and function declarations (not shown here but assumed).

## 📌 Features

- Generic node structure (stores `void*` items)
- Create and add nodes dynamically
- Access nodes by index
- Remove nodes safely
- Destroy the entire list to free memory

## 🔧 Usage

Include the header and use the API functions to manage your linked list:

```c
#include "linkedListDynamic.h"
```

### Create and Add

```c
Node_t *head = NULL;
int *data = malloc(sizeof(int));
*data = 42;
linkedListDynamic_addNode(&head, data);
```

### Get Node

```c
Node_t *node = linkedListDynamic_getNode(head, 0);
if (node != NULL) {
    int *value = (int*)node->item;
    printf("Value: %d\n", *value);
}
```

### Remove Node

```c
linkedListDynamic_removeNode(&head, 0);
```

### Destroy List

```c
linkedListDynamic_destroyList(head);
```

> 💡 Make sure to manage the memory of the data pointed to by `item` if necessary before destroying or removing nodes.

## 📘 API Reference

### `Node_t* linkedListDynamic_createNode(void *item);`

Creates a new node with the given item.

### `void linkedListDynamic_addNode(Node_t** head, void *item);`

Appends a new node at the end of the list.

### `Node_t* linkedListDynamic_getNode(Node_t* head, int index);`

Retrieves the node at a specific index (0-based). Returns `NULL` if out of bounds.

### `void linkedListDynamic_removeNode(Node_t** head, int index);`

Removes the node at the given index and frees its memory.

### `void linkedListDynamic_destroyList(Node_t* head);`

Destroys the entire list, freeing all node memory.

## 🧑‍💻 Author

**Bruno Ragucci**  
Embedded Software Engineer  
📧 bruno [at] ragucci.it

## 📝 License

MIT License  
© 2025 Bruno Ragucci – All rights reserved.

