#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list = (List*) malloc (sizeof(List));
  if (list == NULL)exit(EXIT_FAILURE);
  list->head = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) {
  if (list == NULL || list->head == NULL) {
        return NULL;
  }
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if (list == NULL || list->current == NULL || list->current->next == NULL)return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (list == NULL || list->tail == NULL)return NULL;
  list->current = list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if (list == NULL || list->current == NULL || list->current->prev == NULL)return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node* nodoNuevo = createNode(data);
  if(list == NULL || nodoNuevo == NULL)return;
  nodoNuevo->next = list->head;
  if(list->head == NULL){
    list->head = nodoNuevo;
    list->tail = nodoNuevo;
    list->current = nodoNuevo;
  }
  else {
    nodoNuevo->next = list->head;
    list->head->prev = nodoNuevo;
    list->head = nodoNuevo;
  }
  return;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list == NULL || list->current == NULL)return;
  Node* nodoNuevo = createNode(data);
  if (nodoNuevo == NULL)return;

  if (list->current == list->tail)list->tail = nodoNuevo;
  else{
    nodoNuevo->next = list->current->next;
    list->current->next->prev = nodoNuevo;
  }
  nodoNuevo->prev = list->current;
  list->current->next = nodoNuevo;
  return;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list == NULL || list->current == NULL)return NULL;
  
  void *data = list->current->data;
  Node *nodoABorrar = list->current;

  if (list->current == list->head){
    list->current->next = list->head;
  }
  
  free(*nodoABorrar);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}