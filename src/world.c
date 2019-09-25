#include "world.h"
#include "game_object.h"

size_t WORLD_OBJECT_MAX = 1000;
H_GameObject *WORLD_OBJECTS = NULL;
size_t NEXT_ID = 0;

H_GameObject *H_CreateGameObject()
{
  return &WORLD_OBJECTS[NEXT_ID++];
}

void H_DestroyGameObject(H_GameObject *gameObject)
{
  size_t index = ((size_t)gameObject - (size_t)WORLD_OBJECTS) / sizeof(H_GameObject);

  if (index >= 0 && index < WORLD_OBJECT_MAX)
  {
    WORLD_OBJECTS[index] = (H_GameObject){{0.f, 0.f, 0.f}};
  }
}

void H_CreateWorld()
{
  WORLD_OBJECTS = calloc(WORLD_OBJECT_MAX, sizeof(H_GameObject));
}

void H_DestroyWorld()
{
  if (WORLD_OBJECTS)
  {
    free(WORLD_OBJECTS);
  }
}