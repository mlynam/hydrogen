#ifndef SYSTEMS_CAMERA_H
#define SYSTEMS_CAMERA_H

#include "world.h"
#include "recycled_index.h"
#include "camera.h"

typedef struct _CameraSystem
{
  const unsigned short kMaxCameraCount;
  World *world;
  Camera *cameras;
  int count;
  RecycledIndex *_recycler;
  size_t _next_index;
} CameraSystem;

CameraSystem *CreateCameraSystem(World *, unsigned short max_cameras);
void DestroyCameraSystem(CameraSystem *);
Camera *CreateCamera(CameraSystem *, GameObject *, const vec3 *);
void DestroyCamera(CameraSystem *, Camera *);

#endif
