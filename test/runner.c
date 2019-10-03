#include <check.h>
#include <stdlib.h>
#include <SDL.h>

#include "game_object.h"

START_TEST(test_game_object_default)
{
  GameObject object = _CreateDefaultGameObject();

  ck_assert_float_eq(object.position[0], 0.f);
  ck_assert_float_eq(object.position[1], 0.f);
  ck_assert_float_eq(object.position[2], 0.f);
  ck_assert_float_eq(object.scale[0], 0.f);
  ck_assert_float_eq(object.scale[1], 0.f);
  ck_assert_float_eq(object.scale[2], 0.f);
  ck_assert_float_eq(object.rotation[0], 0.f);
  ck_assert_float_eq(object.rotation[1], 0.f);
  ck_assert_float_eq(object.rotation[2], 0.f);
  ck_assert_int_eq(object.active, true);
  ck_assert_int_eq(object.systems, 0);
}

START_TEST(test_game_object_deserialize)
{
  const unsigned char *yaml =
      "position: !!seq\n"
      "  - 1.0\n"
      "  - 2.0\n"
      "  - 0.0\n"
      "scale: !!seq\n"
      "  - 1.0\n"
      "  - 1.0\n"
      "  - 1.0\n";

  GameObject deserialized = DeserializeGameObject(yaml, 65);

  ck_assert_float_eq(deserialized.position[1], 2.f);
  ck_assert_float_eq(deserialized.scale[0], 1.f);
}

Suite *CreateGameObjectSuite()
{
  Suite *suite;
  TCase *case_core;

  suite = suite_create("GameObject");
  case_core = tcase_create("Core");

  tcase_add_test(case_core, test_game_object_default);
  tcase_add_test(case_core, test_game_object_deserialize);
  suite_add_tcase(suite, case_core);

  return suite;
}

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    return EXIT_FAILURE;
  }

  int number_failed = 0;
  Suite *suite = NULL;
  SRunner *runner;

  if (SDL_strcmp(argv[1], "GameObject") == 0)
  {
    suite = CreateGameObjectSuite();
  }

  if (suite == NULL)
  {
    return EXIT_FAILURE;
  }

  runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return number_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
