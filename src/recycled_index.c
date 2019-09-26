#include "recycled_index.h"

RecycledIndex *CreateRecycledIndex(size_t max_count)
{
  size_t *index = calloc(max_count, sizeof(size_t));
  RecycledIndex init = {max_count, index, 0};

  RecycledIndex *recycled_index = malloc(sizeof(RecycledIndex));

  SDL_memcpy(recycled_index, &init, sizeof(RecycledIndex));

  return recycled_index;
}

void DestroyRecycledIndex(RecycledIndex *recycled_index)
{
  free(recycled_index->index);
  free(recycled_index);

  recycled_index = NULL;
}

size_t *PushIndex(RecycledIndex *recycled_index, size_t index)
{
  if (recycled_index->count >= recycled_index->kMaxElementCount)
  {
    return NULL;
  }

  recycled_index->index[++recycled_index->count] = index;

  return &recycled_index->index[recycled_index->count - 1];
}

size_t PopIndex(RecycledIndex *recycled_index)
{
  size_t index = recycled_index->index[recycled_index->count];

  recycled_index->count--;

  return index;
}
