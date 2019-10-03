#include "yaml.h"

#include "game_object.h"
#include "serialization.h"

SerializationError _DeserializeGameObject(SerializationState *);

GameObject DeserializeGameObject(const unsigned char *input, size_t size)
{
  SerializationError error;
  GameObject object;

  error = Deserialize(&_DeserializeGameObject, &object, input, size);
  if (error == SERIALIZATION_NO_ERROR)
  {
    return object;
  }

  return _CreateDefaultGameObject();
}

SerializationError _DeserializeGameObject(SerializationState *state)
{
  GameObject *object = (GameObject *)state->target;
  int index = state->sequence.current_index;
  const unsigned char *property = state->mapping.current_property;

  if (SDL_strcmp(property, "position") == 0)
  {
    object->position[index] = SDL_atof(state->scalar.value);
  }
  else if (SDL_strcmp(property, "scale") == 0)
  {
    object->scale[index] = SDL_atof(state->scalar.value);
  }
  else if (SDL_strcmp(property, "active") == 0)
  {
    object->active = SDL_atoi(state->scalar.value);
  }
  else if (SDL_strcmp(property, "systems") == 0)
  {
    object->systems = SDL_atoi(state->scalar.value);
  }
  else
  {
    return SERIALIZATION_UNEXPECTED_TOKEN;
  }

  return SERIALIZATION_NO_ERROR;
}

GameObject _CreateDefaultGameObject()
{
  return (GameObject){
      .position = {0.f, 0.f, 0.f},
      .scale = {0.f, 0.f, 0.f},
      .rotation = {0.f, 0.f, 0.f},
      .offset = {0.f, 0.f, 0.f},
      .active = true,
      .systems = 0};
}
