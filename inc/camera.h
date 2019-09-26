#ifndef CAMERA_H
#define CAMERA_H

#include "game_object.h"

typedef struct _Camera
{
  GameObject *game_object;
  const vec3 up;
  mat4 view;
} Camera;

Camera _CreateCamera(GameObject *, const vec3 *);
void LookAt(GameObject *, Camera *);

#endif
