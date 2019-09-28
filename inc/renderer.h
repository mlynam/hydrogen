#ifndef RENDERER_H
#define RENDERER_H

#include "world.h";

typedef struct _Renderer
{

} Renderer;

Renderer *CreateRenderer();
void DestroyRenderer(Renderer *);
void Render(Renderer *, World *);

#endif