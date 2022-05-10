#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "stdio.h"

int main(int argc, const char* argv[]) {
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


    writeChunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    printf("I am working!\n");

    return 0;
}