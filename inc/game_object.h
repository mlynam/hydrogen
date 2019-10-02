#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vec3.h"
#include "systems.h"
#include "SDL.h"

typedef struct _GameObject
{
  vec3 position;
  vec3 scale;
  vec3 rotation;
  vec3 offset;
  bool active;
  SystemTypes systems;
} GameObject;

GameObject DeserializeGameObject(const unsigned char *input, size_t size);
int ReadHandler(void *, char *, int, int *);
GameObject _CreateDefaultGameObject();

#endif
