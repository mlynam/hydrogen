#ifndef SERIALIZATION_H
#define SERIALIZATION_H

typedef struct _SerializationState
{
  char current_property[256];
  int current_index;
  void *target;
  int mapping_beginning;
  int is_sequence;
} SerializationState;

typedef enum _SerializationError
{
  SERIALIZATION_NO_ERROR = 0,
  SERIALIZATION_PARSING_ERROR,
  SERIALIZATION_INVALID_GRAMMAR,
  SERIALIZATION_MAPPING_KEY_TOO_LARGE,
  SERIALIZATION_UNSUPPORTED,
  SERIALIZATION_UNEXPECTED_TOKEN
} SerializationError;

#endif
