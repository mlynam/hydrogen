#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vec3.h"
#include "systems.h"

typedef struct _GameObject
{
  vec3 position;
  vec3 scale;
  vec3 rotation;
  bool active;
  SystemTypes systems;
} GameObject;

GameObject _CreateDefaultGameObject();

#endif
