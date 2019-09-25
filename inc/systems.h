#ifndef SYSTEMS_H
#define SYSTEMS_H

typedef enum _SystemTypes
{
  SYSTEM_SPRITES = 0x01,
  SYSTEM_MESH = 0x02,
  SYSTEM_PHYSICS = 0x04,
  SYSTEM_AI = 0x08,
  SYSTEM_CONTROLLER = 0x16,
  SYSTEM_ANIMATOR = 0x32,
} SystemTypes;

#endif
