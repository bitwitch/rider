#pragma once

#include <stdint.h>

typedef struct {
    size_t length;
    size_t capacity;
    size_t item_size;
    void *items;
} Array_List;

Array_List *array_list_create(size_t item_size, size_t initial_capacity);
void array_list_delete(Array_List *list);
size_t array_list_append(Array_List *list, void *item);
void *array_list_get(Array_List *list, size_t index);
void array_list_remove(Array_List *list, size_t index);
void array_list_remove_n(Array_List *list, size_t index, size_t n);
void array_list_remove_swap(Array_List *list, size_t index);

