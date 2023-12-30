#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "utils/rle.h"
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN,
} OpCode;

typedef struct {
  int capacity;
  int count;
  uint8_t *code;
  RLECollection lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);

int addConstant(Chunk *chunk, Value value);

// given index of the instruction, this function returns the line number
int getLine(Chunk *chunk, int offset);

#endif
