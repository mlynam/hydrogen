#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include "world.h"
#include "systems_camera.h"
#include "yaml.h"

int _cdecl main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

  SDL_Window *window = SDL_CreateWindow(
      "SDL2Test",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  World *world = CreateWorld(10000);
  CameraSystem *cameras = CreateCameraSystem(world, 10);

  GameObject *first = CreateGameObject(world);
  GameObject *second = CreateGameObject(world);

  Camera *camera = CreateCamera(cameras, first, GLM_VEC3_ONE);

  // Setup OpenGL
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (context == NULL)
  {
    printf("OpenGL context could not be created. SDL Error: %s\n", SDL_GetError());
    return -1;
  }

  SDL_GL_SetSwapInterval(1);

  // Render the OpenGL version
  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

  while (SDL_TRUE)
  {
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        break;
      }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
      SDL_Event quit;
      quit.type = SDL_QUIT;

      SDL_PushEvent(&quit);
    }

    glClearColor(.392f, .584f, .929f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
  }

  DestroyGameObject(first, world);

  GameObject *recycled = CreateGameObject(world);
  DestroyWorld(world);

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
