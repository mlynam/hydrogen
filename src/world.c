#include "world.h"
#include "game_object.h"

World *CreateWorld(size_t max_object_count)
{
  GameObject *objects = calloc(max_object_count, sizeof(GameObject));
  RecycledIndex *recycler = CreateRecycledIndex(max_object_count);
  World init = {max_object_count, objects, 0, recycler};

  World *world = malloc(sizeof(World));

  if (world)
  {
    SDL_memcpy(world, &init, sizeof(World));
  }

  return world;
}

void DestroyWorld(World *world)
{
  DestroyRecycledIndex(world->_recycler);

  free(world->game_objects);
  free(world);

  world = NULL;
}

GameObject *CreateGameObject(World *world)
{
  GameObject init = _CreateDefaultGameObject();
  size_t index = world->_recycler->count > 0 ? PopIndex(world->_recycler) : world->_next_game_object_index++;

  GameObject *dest = &world->game_objects[index];

  SDL_memcpy(dest, &init, sizeof(GameObject));

  return dest;
}

void DestroyGameObject(GameObject *gameObject, World *world)
{
  size_t index = IndexOf(gameObject, world);

  if ((index >= 0 || index < world->kMaxGameObjectCount) && PushIndex(world->_recycler, index))
  {
    gameObject->active = false;
  }
}

size_t IndexOf(GameObject *object, World *world)
{
  size_t start = &world->game_objects[0];
  size_t address = object;
  return (address - start) / sizeof(GameObject);
}
