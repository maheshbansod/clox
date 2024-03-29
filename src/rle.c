
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

void writeRLECollection(RLECollection *collection, int data, int count) {
  if (collection->capacity < collection->count + 1) {
    int oldCapacity = collection->capacity;
    collection->capacity = GROW_CAPACITY(oldCapacity);
    collection->entities = GROW_ARRAY(struct rle_entity, collection->entities,
                                      oldCapacity, collection->capacity);
  }

  collection->entities[collection->count].data = data;
  collection->entities[collection->count].count = count;
  collection->count++;
}

static void addNewRLEEntity(RLECollection *collection, int data) {
  writeRLECollection(collection, data, 1);
}

void addRLEData(RLECollection *collection, int data) {
  if (collection->count == 0) {
    addNewRLEEntity(collection, data);
  } else {
    struct rle_entity lastEntity = collection->entities[collection->count - 1];
    if (lastEntity.data == data) {
      lastEntity.count += 1;
    } else {
      addNewRLEEntity(collection, data);
    }
  }
}

// given an offset, it finds the correct data in the collection
int getRLEDataAt(RLECollection *collection, int offset) {
  if (offset < 0 || collection->entities == NULL) {
    return -1;
  }
  int totalTraversed = 0;
  struct rle_entity *current = collection->entities;
  struct rle_entity *last = collection->entities + collection->count - 1;
  while (offset > current->count + totalTraversed) {
    totalTraversed += current->count;
    current++;
    if (current > last) {
      // printf("RLE warning: Invalid RLE index access %d. Size is %d", offset,
      //        collection->count);
      return -1;
    }
  }
  return current->data;
}
