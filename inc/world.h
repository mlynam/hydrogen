/**
 * The world provides memory management for game objects as well as an
 * API for the game object lifecycle.
 */

#ifndef WORLD_H
#define WORLD_H

#include "SDL.h"
#include "game_object.h"

typedef struct _World
{
  const int kMaxGameObjectCount;
  GameObject *game_objects;
  size_t _next_game_object_index;
  size_t *_recycled_indexes;
  size_t _recycled_object_count;
} World;

World *CreateWorld(int max_object_count);
void DestroyWorld(World *);
int GetGameObjectIndex(GameObject *, World *);
GameObject *CreateGameObject(World *);
void DestroyGameObject(GameObject *, World *);

#endif
