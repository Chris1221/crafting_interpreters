#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk; // chunk of code to be executed
  uint8_t* ip; // instruction pointer
  Value stack[STACK_MAX]; // bottom of the stack is element 0 
  Value* stackTop;
} VM;

typedef enum { 
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();


#endif