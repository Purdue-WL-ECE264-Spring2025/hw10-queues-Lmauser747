#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node *new_node = malloc(sizeof(struct list_node));
  new_node->value = value;
  new_node->next = NULL;
  return new_node; 
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *new_head = new_node(value);
  new_head->next = list->head;
  list->head = new_head;
  return;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *new_tail = new_node(value);

  if (list->head == NULL) {
    list->head = new_tail;
    return;
  }

  struct list_node *temp = list->head;
  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = new_tail;
  new_tail->next = NULL;
}

size_t remove_from_head(struct linked_list *list) { 
  struct list_node *temp = list->head->next;
  size_t value = list->head->value;
  free(list->head);

  list->head = temp;

  return value; 
}

size_t remove_from_tail(struct linked_list *list) { 
  if(list->head == NULL){
    return 0;
  }

  struct list_node *temp = list->head;

  if(temp->next == NULL){
    size_t value = temp->value;
    free(temp);
    list->head = NULL;
    return value;
  }

  while(temp->next->next != NULL){
    temp = temp->next;
  }

  size_t value = temp->next->value;
  free(temp->next);

  temp->next = NULL;

  return value; 
}

void free_list(struct linked_list list) {
  struct list_node *temp = list.head;
  struct list_node *temp_2 = temp->next;
  while(temp->next != NULL){
    free(temp);
    temp = temp_2;
    temp_2 = temp->next;
  }

  free(temp);
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
