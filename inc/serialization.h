#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "yaml.h"

typedef enum _SerializationError
{
  SERIALIZATION_NO_ERROR = 0,
  SERIALIZATION_PARSING_ERROR,
  SERIALIZATION_INVALID_GRAMMAR,
  SERIALIZATION_MAPPING_KEY_TOO_LARGE,
  SERIALIZATION_UNSUPPORTED,
  SERIALIZATION_UNEXPECTED_TOKEN
} SerializationError;

typedef struct _SerializationState
{
  /**
   * Pointer to the struct we are [de]serializing.
   */
  void *target;

  /**
   * Stores data for the current mapping state.
   */
  struct MappingState
  {
    const unsigned char current_property[256];

    /**
     * If we have a `current_property` and the left-hand side is not resolved,
     * (rhs_resolve ::= 0), then we are parsing the left-hand side. Any completed node
     * will resolve a rhs during a mapping.
     */
    const int rhs_resolved;
  } mapping;

  /**
   * Stores sequence data for the serialization. If `current_index > -1` then we are
   * parsing a sequence.
   */
  struct SequenceState
  {
    /**
     * The serialization system will manages the current_index.
     */
    const int current_index;
  } sequence;

  /**
   * Scalars are leaf nodes in the yaml tree. If the current event is scalar, `scalar::value`
   * will have a string value. Conversely, if the current event is not a scalar, `scalar::value`
   * will equal the NUL char, '\0'.
   */
  struct ScalarState
  {
    const unsigned char value[256];
    const size_t length;
  } scalar;

  yaml_parser_t *_parser;
  yaml_event_t *_event;
  yaml_event_type_t _last_event_type;
} SerializationState;

typedef SerializationError DeserializeHandler(SerializationState *state);

SerializationError Deserialize(
    DeserializeHandler *,
    void *,
    const unsigned char *,
    size_t);

#endif
