#include "game_object.h"

GameObject _CreateDefaultGameObject()
{
  return (GameObject){
      .position = {0.f, 0.f, 0.f},
      .scale = {0.f, 0.f, 0.f},
      .rotation = {0.f, 0.f, 0.f},
      .active = true,
      .systems = 0};
}
