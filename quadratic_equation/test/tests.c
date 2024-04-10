#include "tests.h"

int main(void) {
  int failed = 0;

  Suite *suites[] = {test_solve_equation(), NULL};

  SRunner *sr = srunner_create(NULL);

  // srunner_set_log(sr, "test_log.txt");
  srunner_set_fork_status(sr, CK_FORK); // CK_NOFORK

  for (int i = 0; suites[i] != NULL; i++) {
    srunner_add_suite(sr, suites[i]);
  }

  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed;
}
