#include "yaml.h"

#include "game_object.h"
#include "serialization.h"

typedef int Handler(
    yaml_parser_t *parser,
    yaml_event_t *event,
    SerializationState *state);

Handler Begin;
Handler Document;
Handler Node;

int Parse(Handler *handler, yaml_parser_t *parser, yaml_event_t *event, yaml_event_type_t sentinel, SerializationState *state)
{
  int error = SERIALIZATION_NO_ERROR;

  while (yaml_parser_parse(parser, event) && event->type != sentinel && !error)
  {
    error = handler(parser, event, state);
  }

  return error;
}

GameObject DeserializeGameObject(const unsigned char *input, size_t size)
{
  yaml_parser_t parser;
  yaml_event_t event;
  GameObject object;
  SerializationState state;
  int result;

  state = (SerializationState){
      .current_property = '\0',
      .current_index = 0,
      .mapping_beginning = 0,
      .is_sequence = 0};
  state.target = &object;

  yaml_parser_initialize(&parser);
  yaml_parser_set_input_string(&parser, input, size);

  result = Parse(&Begin, &parser, &event, YAML_STREAM_END_EVENT, &state);

  return object;
}

int Begin(yaml_parser_t *parser, yaml_event_t *event, SerializationState *state)
{
  switch (event->type)
  {
  case YAML_STREAM_START_EVENT:
    return Parse(&Document, parser, event, YAML_DOCUMENT_END_EVENT, state);
  default:
    return SERIALIZATION_INVALID_GRAMMAR;
  }
}

int Document(yaml_parser_t *parser, yaml_event_t *event, SerializationState *state)
{
  switch (event->type)
  {
  case YAML_DOCUMENT_START_EVENT:
    return Parse(&Node, parser, event, YAML_DOCUMENT_END_EVENT, state);
  default:
    return SERIALIZATION_INVALID_GRAMMAR;
  }
}

int Node(yaml_parser_t *parser, yaml_event_t *event, SerializationState *state)
{
  switch (event->type)
  {
  case YAML_SCALAR_EVENT:
    return HandleScalar(event, state);
  case YAML_MAPPING_START_EVENT:
    state->mapping_beginning = 1;
    return Parse(&Node, parser, event, YAML_MAPPING_END_EVENT, state);
  case YAML_SEQUENCE_START_EVENT:
    state->current_index = 0;
    state->is_sequence = 1;
    int sequence_result = Parse(&Node, parser, event, YAML_SEQUENCE_END_EVENT, state);
    state->current_index = 0;
    state->is_sequence = 1;
    return sequence_result;
  default:
    return SERIALIZATION_INVALID_GRAMMAR;
  }
}

int HandleScalar(yaml_event_t *event, SerializationState *state)
{
  if (state->mapping_beginning)
  {
    state->mapping_beginning = 0;

    if (event->data.scalar.length > 256)
    {
      return SERIALIZATION_MAPPING_KEY_TOO_LARGE;
    }

    SDL_utf8strlcpy(state->current_property, event->data.scalar.value, event->data.scalar.length + 1);
  }
  else if (state->is_sequence)
  {
    if (SDL_strcmp(state->current_property, "position") == 0)
    {
      ((GameObject *)state->target)->position[state->current_index++] = SDL_atof(event->data.scalar.value);
    }
    else if (SDL_strcmp(state->current_property, "scale") == 0)
    {
      ((GameObject *)state->target)->scale[state->current_index++] = SDL_atof(event->data.scalar.value);
    }
    else
    {
      return SERIALIZATION_UNEXPECTED_TOKEN;
    }
  }
  else
  {
    if (SDL_strcmp(state->current_property, "active") == 0)
    {
      ((GameObject *)state->target)->active = SDL_atoi(event->data.scalar.value);
    }
    else if (SDL_strcmp(state->current_property, "systems") == 0)
    {
      ((GameObject *)state->target)->systems = SDL_atoi(event->data.scalar.value);
    }
    else
    {
      return SERIALIZATION_UNEXPECTED_TOKEN;
    }
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
