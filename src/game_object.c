#include "game_object.h"
#include "yaml.h"

GameObject DeserializeGameObject(FILE *file)
{
  yaml_parser_t parser;
  yaml_token_t token;
  GameObject object;
  char key[256];

  yaml_parser_initialize(&parser);

  yaml_parser_set_input_file(&parser, file);

  do
  {
    yaml_parser_scan(&parser, &token);

    switch (token.type)
    {
    case YAML_STREAM_START_TOKEN:
      break;
    case YAML_KEY_TOKEN:
      SDL_strlcpy(key, token.end_mark.column - token.start_mark.column, token.data.alias.value);
      break;
    case YAML_BLOCK_ENTRY_TOKEN:
      break;
    default:
      break;
    }
  } while (token.type != YAML_STREAM_END_TOKEN);
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
