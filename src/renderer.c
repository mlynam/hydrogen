#include "renderer.h"
#include "SDL.h"

Renderer *CreateRenderer()
{
  Renderer init;
  Renderer *renderer = malloc(sizeof(Renderer));

  SDL_memcpy(renderer, &init, sizeof(Renderer));

  return renderer;
}

void DestroyRenderer(Renderer *renderer)
{
  free(renderer);
}

void Render(Renderer *renderer, World *world)
{
}