/**
 *  \file linkedListDynamic.h
 *  
 *  \author Bruno Ragucci - Embedded Software Engineer
 *  \n mail : bruno (at) ragucci.it
 *  
 *  \date 12 APR 2025
 *  
 *  @brief Dynamic linked list API for generic item storage.
 *
 *  \copyright Copyright (c) 2025 by Bruno Ragucci - All rights reserved.
 *  \n
 *  \license MIT
 */

 #ifndef __LINKED_LIST_DYNAMIC_H__
 #define __LINKED_LIST_DYNAMIC_H__
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 /**
  * @brief Node structure for dynamic linked list.
  */
 typedef struct Node {
     void *item;           /**< Pointer to data */
     struct Node *next;    /**< Pointer to next node */
 } Node_t;
 
 /**
  * @brief Create a new node with the given item.
  * 
  * @param item Pointer to the item to store
  * @return Node_t* Pointer to the newly created node
  */
 Node_t* linkedListDynamic_createNode(void *item);
 
 /**
  * @brief Add a new node at the end of the list.
  * 
  * @param head Pointer to the head of the list
  * @param item Pointer to the item to add
  */
 void linkedListDynamic_addNode(Node_t** head, void *item);
 
 /**
  * @brief Get a node by index from the list.
  * 
  * @param head Pointer to the head of the list
  * @param index Index of the node to retrieve
  * @return Node_t* Pointer to the node at the given index, or NULL if not found
  */
 Node_t* linkedListDynamic_getNode(Node_t* head, int index);
 
 /**
  * @brief Remove a node at the given index from the list.
  * 
  * @param head Pointer to the head of the list
  * @param index Index of the node to remove
  */
 void linkedListDynamic_removeNode(Node_t** head, int index);
 
 /**
  * @brief Destroy the entire list and free memory.
  * 
  * @param head Pointer to the head of the list
  */
 void linkedListDynamic_destroyList(Node_t* head);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // __LINKED_LIST_DYNAMIC_H__
 