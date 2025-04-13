/**
 *  \file linkedListDynamic.c
 *  
 *  \author Bruno Ragucci - Embedded Software Engineer
 *  \n mail : bruno (at) ragucci.it
 *  
 *  \date 12 APR 2025
 *  
 *  @brief Dynamic linked list implementation for generic item storage.
 *
 *  \copyright Copyright (c) 2025 by Bruno Ragucci - All rights reserved.
 *  \n
 *  \license MIT
 */

 #include <stdlib.h>
 #include "linkedListDynamic.h"
 
 Node_t* linkedListDynamic_createNode(void *item)
 {
     Node_t* node = (Node_t*)malloc(sizeof(Node_t));
     if (node != NULL) {
         node->item = item;
         node->next = NULL;
     }
     return node;
 }
 
 void linkedListDynamic_addNode(Node_t** head, void *item)
 {
     Node_t* newNode = linkedListDynamic_createNode(item);
     if (newNode == NULL) return;
 
     if (*head == NULL) {
         *head = newNode;
     } else {
         Node_t* current = *head;
         while (current->next != NULL) {
             current = current->next;
         }
         current->next = newNode;
     }
 }
 
 Node_t* linkedListDynamic_getNode(Node_t* head, int index)
 {
     int count = 0;
     Node_t* current = head;
     while (current != NULL) {
         if (count == index) {
             return current;
         }
         count++;
         current = current->next;
     }
     return NULL;
 }
 
 void linkedListDynamic_removeNode(Node_t** head, int index)
 {
     if (*head == NULL || index < 0) return;
 
     Node_t* temp = *head;
 
     if (index == 0) {
         *head = temp->next;
         free(temp);
         return;
     }
 
     for (int i = 0; temp != NULL && i < index - 1; i++) {
         temp = temp->next;
     }
 
     if (temp == NULL || temp->next == NULL) return;
 
     Node_t* next = temp->next->next;
     free(temp->next);
     temp->next = next;
 }
 
 void linkedListDynamic_destroyList(Node_t* head)
 {
     Node_t *node = head;
     while (node != NULL) {
         Node_t *next = node->next;
         free(node);
         node = next;
     }
 }
 