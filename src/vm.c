#include "common.h"
#include "debug.h"
#include "vm.h"
#include "stdio.h"

// This is a single global
// virtual machine that will
// be used by everything.  
VM vm; 

static void resetStack() { 
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {
}


// push a value onto the top of the stack
// this dereferences the poitner to the 
// top of the stack and assigns the value
// there, then increments the stack pointer
void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}


// take a value off the top 
// of the stack and return it
// decrease the value of the stack
// top poitner. 
Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run() { 
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
      double b = pop(); \
      double a = pop(); \
      push(a op b); \
    } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    // basically loop over all the values 
    // in the stack and print them out one
    // by one
    printf("          ");
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk,
                           (int)(vm.ip - vm.chunk->code));
#endif 

    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            push(constant);
            break;
        }
        case OP_ADD:      BINARY_OP(+); break;
        case OP_SUBTRACT: BINARY_OP(-); break;
        case OP_MULTIPLY: BINARY_OP(*); break;
        case OP_DIVIDE:   BINARY_OP(/); break;
        case OP_NEGATE: {
            push(-pop()); 
            break;
        }
        case OP_RETURN: {
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
        }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code; // IP means instruction pointer.
    return run();
}