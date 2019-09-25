#include "SDL.h"
#include "world.h"

int _cdecl main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

  SDL_Window *window = SDL_CreateWindow(
      "SDL2Test",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      0);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  World *world = CreateWorld(10000);

  GameObject *first = CreateGameObject(world);
  GameObject *second = CreateGameObject(world);

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

    float s = SDL_GetTicks() / 1000.f;
    float r = SDL_sinf(s);
    if (r < 0)
    {
      r *= -1;
    }

    first->position[0] = r;

    SDL_SetRenderDrawColor(renderer, r * 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  DestroyGameObject(first, world);

  GameObject *recycled = CreateGameObject(world);
  DestroyWorld(world);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
