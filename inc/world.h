/**
 * The world provides memory management for game objects as well as an
 * API for the game object lifecycle.
 */

#ifndef WORLD_H
#define WORLD_H

#include "SDL.h"
#include "game_object.h"
#include "recycled_index.h"

typedef struct _World
{
  const size_t kMaxGameObjectCount;
  GameObject *game_objects;
  size_t _next_game_object_index;
  RecycledIndex *_recycler;
} World;

World *CreateWorld(size_t max_object_count);
void DestroyWorld(World *);
int GetGameObjectIndex(GameObject *, World *);
GameObject *CreateGameObject(World *);
void DestroyGameObject(GameObject *, World *);
size_t IndexOf(GameObject *, World *);

#endif
