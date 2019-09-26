#include "systems_camera.h"

CameraSystem *CreateCameraSystem(World *world, unsigned short max_cameras)
{
  Camera *cameras = calloc(max_cameras, sizeof(Camera));
  RecycledIndex *recycler = CreateRecycledIndex(max_cameras);
  CameraSystem init = {
      .kMaxCameraCount = max_cameras,
      .world = world,
      .cameras = cameras,
      .count = 0,
      ._recycler = recycler,
      ._next_index = 0};

  CameraSystem *system = malloc(sizeof(CameraSystem));
  if (system == 0)
  {
    return NULL;
  }

  SDL_memcpy(system, &init, sizeof(CameraSystem));

  return system;
}

void DestroyCameraSystem(CameraSystem *system)
{
  DestroyRecycledIndex(system->_recycler);

  free(system->cameras);
  free(system);

  system = NULL;
}

Camera *CreateCamera(CameraSystem *system, GameObject *attach_to, const vec3 *up)
{
  size_t index = system->_recycler->count > 0 ? PopIndex(system->_recycler) : system->_next_index++;
  Camera init = _CreateCamera(attach_to, up);
  Camera *camera = &system->cameras[index];

  SDL_memcpy(camera, &init, sizeof(Camera));

  return camera;
}

void DestroyCamera(CameraSystem *system, Camera *camera)
{
}
