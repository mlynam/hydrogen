#include <SDL.h>

#include "serialization.h"
#include "constants.h"

typedef int TreeVisitor(SerializationState *state, DeserializeHandler *handler);
typedef void StateInitializer(SerializationState *state);

TreeVisitor _Start;
TreeVisitor _Document;
TreeVisitor _Node;
StateInitializer _SetDefaultMapping;
StateInitializer _SetDefaultSequence;
StateInitializer _SetDefaultScalar;

SerializationError Deserialize(
    DeserializeHandler *handler,
    void *target,
    const unsigned char *data,
    size_t length)
{
  yaml_parser_t parser;
  yaml_event_t event;
  SerializationState state;
  int result;

  state.target = target;
  state._parser = &parser;
  state._event = &event;
  state._last_event_type = YAML_NO_EVENT;

  _SetDefaultMapping(&state);
  _SetDefaultSequence(&state);
  _SetDefaultScalar(&state);

  yaml_parser_initialize(&parser);
  yaml_parser_set_input_string(&parser, data, length);

  return _Parse(&_Start, YAML_NO_EVENT, &state, handler);
}

int _Parse(
    TreeVisitor *visitor,
    yaml_event_type_t sentinel,
    SerializationState *state,
    DeserializeHandler *handler)
{
  int error = SERIALIZATION_NO_ERROR;
  yaml_parser_t *parser = state->_parser;
  yaml_event_t *event = state->_event;

  while (yaml_parser_parse(parser, event) && event->type != sentinel && !error)
  {
    error = visitor(state, handler);
  }

  return error;
}

int _Start(SerializationState *state, DeserializeHandler *handler)
{
  switch (state->_event->type)
  {
  case YAML_STREAM_START_EVENT:
    return _Parse(&_Document, YAML_STREAM_END_EVENT, state, handler);
  default:
    return SERIALIZATION_INVALID_GRAMMAR;
  }
}

int _Document(SerializationState *state, DeserializeHandler *handler)
{
  switch (state->_event->type)
  {
  case YAML_DOCUMENT_START_EVENT:
    return _Parse(&_Node, YAML_DOCUMENT_END_EVENT, state, handler);
  default:
    return SERIALIZATION_INVALID_GRAMMAR;
  }
}

int _Node(SerializationState *state, DeserializeHandler *handler)
{
  SerializationError error;
  yaml_event_t *event;

  event = state->_event;

  switch (event->type)
  {
  /**
   * Resolve mapping rhs, sequence indexing if necessary. Sequence and mapping starts (and
   * endings, technically) set the mapping and sequence state so we always invoke the
   * handler first, and then resolve sequence or mapping changes.
   */
  case YAML_SCALAR_EVENT:
    int mapping_block_started = state->_last_event_type == YAML_MAPPING_START_EVENT;
    int scalar_rhs = state->mapping.current_property != '\0' && state->mapping.rhs_resolved == 1;
    int sequence_rhs = state->mapping.current_property != '\0' && state->_last_event_type == YAML_SEQUENCE_END_EVENT;

    // If any of these scenarios are true, then this new scalar is the start of a new mapping KVP.
    if (mapping_block_started || scalar_rhs || sequence_rhs)
    {
      SDL_memcpy(&state->mapping.rhs_resolved, &kZero, sizeof(int));
      SDL_utf8strlcpy(
          state->mapping.current_property,
          event->data.scalar.value,
          event->data.scalar.length + 1);

      state->_last_event_type = YAML_SCALAR_EVENT;

      return SERIALIZATION_NO_ERROR;
    }

    SDL_utf8strlcpy(state->scalar.value, event->data.scalar.value, event->data.scalar.length + 1);
    SDL_memcpy(&state->scalar.length, &event->data.scalar.length, sizeof(size_t));

    error = handler(state);

    // A sequence::current_index > -1 indicates that we are inside a sequence block. We need
    // to increment the index before handling the next event.
    if (state->sequence.current_index > -1)
    {
      int next_index;
      next_index = state->sequence.current_index + 1;
      SDL_memcpy(&state->sequence.current_index, &next_index, sizeof(int));
    }
    // If this scalar event follows a previous scalar event and the handler processed it, then we have
    // resolved the RHS of a mapping
    else if (state->mapping.current_property != '\0' && state->_last_event_type == YAML_SCALAR_EVENT)
    {
      SDL_memcpy(&state->mapping.rhs_resolved, &kOne, sizeof(int));
    }

    state->_last_event_type = YAML_SCALAR_EVENT;

    return error;

  case YAML_MAPPING_START_EVENT:
    state->_last_event_type = YAML_MAPPING_START_EVENT;
    error = _Parse(&_Node, YAML_MAPPING_END_EVENT, state, handler);
    state->_last_event_type = YAML_MAPPING_END_EVENT;

    _SetDefaultMapping(state);

    return error;

  // When we start a new sequence block, we need to set sequence::current_index to 0
  // to signal to our handler that they need to process nodes as elements in the
  // sequence block.
  case YAML_SEQUENCE_START_EVENT:
    state->_last_event_type = YAML_SEQUENCE_START_EVENT;

    SDL_memcpy(&state->sequence.current_index, &kZero, sizeof(int));

    error = _Parse(&_Node, YAML_SEQUENCE_END_EVENT, state, handler);
    state->_last_event_type = YAML_SEQUENCE_END_EVENT;

    _SetDefaultSequence(state);

    return error;

  case YAML_ALIAS_EVENT:
    state->_last_event_type = YAML_ALIAS_EVENT;
    return SERIALIZATION_UNSUPPORTED;

  default:
    return SERIALIZATION_INVALID_GRAMMAR;
  }
}

void _SetDefaultMapping(SerializationState *state)
{
  SDL_utf8strlcpy(state->mapping.current_property, &kNul, 1);
  SDL_memcpy(&state->mapping.rhs_resolved, &kZero, sizeof(int));
}

void _SetDefaultSequence(SerializationState *state)
{
  SDL_memcpy(&state->sequence.current_index, &kMinusOne, sizeof(int));
}

void _SetDefaultScalar(SerializationState *state)
{
  SDL_utf8strlcpy(&state->scalar.value, &kNul, 1);
  SDL_memcpy(&state->scalar.length, &kOne, sizeof(int));
}
