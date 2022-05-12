#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  initValueArray(&chunk->lines);
  initValueArray(&chunk->constants);

  // for experiment
  chunk->line_idx = 0; 
}

// clear the memory allocated to the chunk
void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
        oldCapacity, chunk->capacity);

    // This may be overly zealous 
    chunk->lines = GROW_ARRAY(int, chunk->lines,
        oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;

  // this is what I need to modify, basically.
  // Take in the state of the current line, 
  // if it is different (or if it is the last line) 
  // we need to store that. 
  //
  // so chunk -> lines will look like 
  // [count, line number, count, line number]
  //
  // what if I store the last line number in the chunk?
  // then I could check against it and see if it has changed
  // but then I have the issue of how to know when we're done...
  // 
  // I could also just overwrite the value, rather than adding on?
  // maybe that's the best approach. Then I could store the current
  // idx of the line number. yea okay I like that.  

  // 1. find the idx of the instruction or store it if it doesn't exist
  // 2. if the line number is the same, incremement the idx-1 element
  // 3. if the line number is not the same, (grow the array) and add the 
  //    new line number at the idx + 2 element, adding a 1 at the idx + 1
  //    element. 
  // 4. Update the idx that is stored in the chunk
  chunk->lines[chunk->count] = line;

  chunk->count++;
}

// add some data.
int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}


