#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  
  // free is std lib (i think)
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  // realloc is base C standard library function
  // similar to malloc when oldsize is 0 
  void* result = realloc(pointer, newSize);

  // there's no perfection in life  
  if (result == NULL) exit(1);
  return result;
}