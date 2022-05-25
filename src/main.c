#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "stdio.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
    initVM();

    Chunk chunk; 
    initChunk(&chunk);

    // return the idx of the constant 
    // in the constant pool 
    int constant = addConstant(&chunk, 1.2);

    // the first is the opcode for the constant
    writeChunk(&chunk, OP_CONSTANT, 123);
    // then we add the actual address of the 
    // constant.
    writeChunk(&chunk, constant, 123);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIVIDE, 123);
    writeChunk(&chunk, OP_NEGATE, 123);


    writeChunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    printf("I am working!\n");

    return 0;
}