#include <check.h>
#include <stdlib.h>
#include <SDL.h>

#include "game_object.h"

START_TEST(test_game_object_default)
{
  GameObject object = _CreateDefaultGameObject();

  ck_assert_float_eq(object.position[0], 0.f);
}

Suite *CreateGameObjectSuite()
{
  Suite *suite;
  TCase *case_core;

  suite = suite_create("GameObject");
  case_core = tcase_create("Core");

  tcase_add_test(case_core, test_game_object_default);
  suite_add_tcase(suite, case_core);

  return suite;
}

int main(int argc, char const *argv[])
{
  if (argc != 1)
  {
    printf_s(
        "You must specify one suite to run:\n\tGameObject");

    return EXIT_FAILURE;
  }

  int number_failed = 0;
  Suite *suite = NULL;
  SRunner *runner;

  if (SDL_strcmp(argv[0], "GameObject"))
  {
    suite = CreateGameObjectSuite();
  }
  else
  {
    /* code */
    printf_s("Test suite not found.");
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
