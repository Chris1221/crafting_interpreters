#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"


// Define opcodes
typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;

// A struct to hold a chunk of code
typedef struct {
  int count;  // Number of instructions in use
  int capacity;  // Number of instructions allocated
  uint8_t* code;
  //int* lines;
  ValueArray lines; // new arary to hold the lines
  ValueArray constants; // the data 

  int line_idx; // which line is currently being stored
} Chunk;

// No constructors so here's one
void initChunk(Chunk* chunk);
// free the memory allocated to the chunk
void freeChunk(Chunk* chunk);
// Appending an instruction to the chunk
void writeChunk(Chunk* chunk, uint8_t byte, int line);
// convenience method to add some constants
int addConstant(Chunk* chunk, Value value);

#endif