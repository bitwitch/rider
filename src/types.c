#include <stdlib.h>
#include "types.h"
#include "util.h"

Array_List *array_list_create(size_t item_size, size_t initial_capacity) {
    Array_List *list = malloc(sizeof(Array_List));
    if (!list)
        ERROR_EXIT("array_list_create: malloc failed to allocate %zu bytes for Array_List\n", sizeof(Array_List));

    list->items = malloc(item_size * initial_capacity);

    if (!list->items)
        ERROR_EXIT("array_list_create: malloc failed to allocate %zu bytes for Array_List.items\n", item_size*initial_capacity);

    list->item_size = item_size;
    list->capacity = initial_capacity;
    list->length = 0;

    return list;
}

size_t array_list_append(Array_List *list, void *item) {
    if (list->length == list->capacity) {
        list->capacity = list->capacity == 0 ? 1 : list->capacity*2;
        void *items = realloc(list->items, list->item_size * list->capacity);
        if (!items) 
            ERROR_EXIT("array_list_append: realloc failed to allocate %zu bytes for Array_List.items\n", list->item_size*list->capacity);
        list->items = items;
    }

    size_t index = list->length++;
    void *dest = (uint8_t*)list->items + index * list->item_size;
    memcpy(dest, item, list->item_size);
    return index;
}

void *array_list_get(Array_List *list, size_t index) {
    if (index >= list->length)
        ERROR_RETURN(NULL, "array_list_get: Index out of bounds: %zu\n", index);
    return (uint8_t*)list->items + index * list->item_size;
}

void array_list_remove(Array_List *list, size_t index) {
    array_list_remove_n(list, index, 1);
}

void array_list_remove_n(Array_List *list, size_t index, size_t n) {
    if (list->length == 0)
        ERROR_EXIT("array_list_remove_n: List is empty\n");
    if (index + n >= list->length)
        ERROR_EXIT("array_list_remove_n: Index out of bounds: %zu\n", index+n);

    uint8_t *start = (uint8_t*)list->items + (index * list->item_size);
    uint8_t *end = (uint8_t*)list->items + ((index + n) * list->item_size);

    int items_to_move = list->length - (index + n);

    memmove(start, end, list->item_size*items_to_move);
}

// swaps the last element in the array for the element to be removed. O(1) time.
// does not preserve array order and may invalidate any handles to the element that
// is swapped
void array_list_remove_swap(Array_List *list, size_t index) {
    if (list->length == 0)
        ERROR_EXIT("array_list_remove_swap: List is empty\n");
    if (index >= list->length)
        ERROR_EXIT("array_list_remove_swap: Index out of bounds: %zu\n", index);

    uint8_t *dest = (uint8_t*)list->items + (index * list->item_size);
    uint8_t *src = (uint8_t*)list->items + ((list->length-1) * list->item_size);

    memcpy(dest, src, list->item_size);
}

void array_list_delete(Array_List *list) {
    if (list) {
        if (list->items) 
            free(list->items);
        free(list);
    }
}
