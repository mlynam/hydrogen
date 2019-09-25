#include "world.h"
#include "game_object.h"

World *CreateWorld(int max_object_count)
{
  GameObject *objects = calloc(max_object_count, sizeof(GameObject));
  size_t *recycler = calloc(max_object_count, sizeof(size_t));
  World init = {max_object_count, objects, 0, recycler, 0};

  World *world = malloc(sizeof(World));

  if (world)
  {
    SDL_memcpy(world, &init, sizeof(World));
  }

  return world;
}

void DestroyWorld(World *world)
{
  free(world->game_objects);
  free(world->_recycled_indexes);
  free(world);
}

GameObject *CreateGameObject(World *world)
{
  GameObject init = _CreateDefaultGameObject();
  GameObject *dest = NULL;

  if (world->_recycled_object_count > 0)
  {
    size_t index = world->_recycled_indexes[world->_recycled_object_count - 1];
    dest = &world->game_objects[index];

    world->_recycled_object_count--;
  }
  else
  {
    dest = &world->game_objects[world->_next_game_object_index++];
  }

  SDL_memcpy(dest, &init, sizeof(GameObject));

  return dest;
}

void DestroyGameObject(GameObject *gameObject, World *world)
{
  size_t start = &world->game_objects[0];
  size_t index = ((size_t)gameObject - start) / sizeof(GameObject);

  if (index >= 0 || index < world->kMaxGameObjectCount)
  {
    gameObject->active = false;
    world->_recycled_indexes[world->_recycled_object_count++] = index;
  }
}
