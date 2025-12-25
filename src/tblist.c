#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "tblist.h"
#include "tbdefines.h"

tblist* tblist_create(size_t capacity)
{
    tblist* list = malloc(sizeof(tblist));
    if(!list)
    {
       list = NULL;
       fprintf(stderr, "error: could not allocate list memory.\n");
       return (tblist*){0};
 
    }

    list->capacity = capacity;
    list->count = 0;
    list->elms = malloc(sizeof(void*) * capacity);
    
    if(!list->elms)
    {
       list->elms = NULL;
       fprintf(stderr, "error: could not allocate list.elms memory.\n");
       return (tblist*){0};
    }

    return list;
}

void tblist_increase_capacity(tblist* list, size_t newCapacity)
{
   if(list->capacity >= newCapacity)
   {
        fprintf(stderr, "warning: cannot increase capacity, new list capacity is less than or equal to current capacity (new-capacity: %zu)\n", newCapacity);
        return;
   }

   void** upsize = malloc(sizeof(void*) * newCapacity);
   if(list->elms)
   {
     for(size_t i = 0; i < list->count; i++)
        upsize[i] = list->elms[i];
   }
   
   free(list->elms);
   list->elms = upsize;
}


_bool tblist_append(tblist* list, void* data)
{
    if(!list || !list->elms)
    {
        fprintf(stderr, "error: no valid list provided\n");
        return _false;
    }

    if(list->count >= list->capacity)
        tblist_increase_capacity(list, list->capacity * 2);

    list->elms[list->count] = data;
    list->count++;
    return _true;
}


_bool tblist_remove(tblist* list, void* data)
{ 
    if(!data)
    {
        fprintf(stderr, "error: cannot remove, provided element ptr is not valid\n");
        return _false;
    }
    if(!list || !list->elms)
    {
        fprintf(stderr, "error: no valid list provided\n");
        return _false;
    }

    for(size_t i = 0; i < list->count; i++)
        if(list->elms[i] == data)
            return tblist_remove_at(list, i);

    return _false;
}

_bool tblist_remove_at(tblist* list, size_t index)
{
    if(!list || !list->elms)
    {
        fprintf(stderr, "error: no valid list provided\n");
        return _false;
    }
    if(index >= list->count)
    {
        fprintf(stderr, "error: list-element index out of range (index: %zu)\n", index);
        return _false;
    }

    list->elms[index] = NULL;
    for(size_t i = index + 1; i < list->count; i++)
        list->elms[i - 1] = list->elms[i];
    return _true;
}

void* tblist_get(tblist* list, size_t index)
{
    if(!list || !list->elms)
    {
        fprintf(stderr, "error: no valid list provided\n");
        return NULL;
    }
    if(index >= list->count)
    {
        fprintf(stderr, "error: list-element index out of range (index: %zu)\n", index);
        return NULL;
    }
    return list->elms[index];
}






































