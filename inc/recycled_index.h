#ifndef RECYCLED_INDEX_H
#define RECYCLED_INDEX_H

#include "SDL.h"

typedef struct _RecycledIndex
{
  const size_t kMaxElementCount;
  size_t *index;
  size_t count;
} RecycledIndex;

RecycledIndex *CreateRecycledIndex(size_t max_count);
void DestroyRecycledIndex(RecycledIndex *);
size_t *PushIndex(RecycledIndex *, size_t index);
size_t PopIndex(RecycledIndex *);

#endif
