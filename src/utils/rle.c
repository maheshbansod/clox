
#include "rle.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

void initRLECollection(RLECollection *collection) {
  collection->count = 0;
  collection->capacity = 0;
  collection->entities = NULL;
}

void freeRLECollection(RLECollection *collection) {
  FREE_ARRAY(struct rle_entity, collection->entities, collection->capacity);
  initRLECollection(collection);
}

void writeRLECollection(RLECollection *collection, struct rle_entity *value) {
  if (collection->capacity < collection->count + 1) {
    int oldCapacity = collection->capacity;
    collection->capacity = GROW_CAPACITY(oldCapacity);
    collection->entities = GROW_ARRAY(struct rle_entity *, collection->entities,
                                      oldCapacity, collection->capacity);
  }

  collection->entities[collection->count] = value;
  collection->count++;
}

static void addNewRLEEntity(RLECollection *collection, int data) {
  struct rle_entity *newEntity = malloc(sizeof(struct rle_entity));
  newEntity->count = 1;
  newEntity->data = data;
  writeRLECollection(collection, newEntity);
}

void addRLEData(RLECollection *collection, int data) {
  if (collection->count == 0) {
    addNewRLEEntity(collection, data);
  } else {
    struct rle_entity *lastEntity = collection->entities[collection->count - 1];
    if (lastEntity->data == data) {
      lastEntity->count += 1;
    } else {
      addNewRLEEntity(collection, data);
    }
  }
}

// given an offset, it finds the correct data in the collection
int getRLEDataAt(RLECollection *collection, int offset) {
  if (offset < 0) {
    return -1;
  }
  int collectionOffset = 0, totalTraversed = 0;
  struct rle_entity *current = collection->entities[collectionOffset];
  while (offset > current->count + totalTraversed) {
    totalTraversed += current->count;
    collectionOffset += 1;
    if (collectionOffset >= collection->count) {
      // printf("RLE warning: Invalid RLE index access %d. Size is %d", offset,
      //        collection->count);
      return -1;
    }
    current = collection->entities[collectionOffset];
  }
  return current->data;
}
