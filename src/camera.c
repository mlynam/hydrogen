#include "camera.h"
#include "cglm.h"

void LookAt(GameObject *object, Camera *camera)
{
}

Camera _CreateCamera(GameObject *object, const vec3 *up)
{
  Camera cam;
  cam.game_object = object;

  mat4 view = GLM_MAT4_IDENTITY_INIT;

  SDL_memcpy(&cam.view, &view, sizeof(mat4));
  SDL_memcpy(&cam.up, up, sizeof(vec3));

  return cam;
}
