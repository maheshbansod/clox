#ifndef clox_rle_impl_h
#define clox_rle_impl_h

struct rle_entity {
  int data;
  int count;
};

typedef struct {
  int capacity;
  int count;
  struct rle_entity **entities;
} RLECollection;

/** Get entity at a particular offset */
int getRLEDataAt(RLECollection *collection, int offset);

/** add entity to collection */
void addRLEData(RLECollection *collection, int data);

void initRLECollection(RLECollection *collection);
void freeRLECollection(RLECollection *collection);

#endif
