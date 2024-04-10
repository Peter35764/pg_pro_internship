#include "../tests.h"

START_TEST(test0_err1) {
  double a = 0;
  double b = 0;
  double c = 0;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test0_err2) {
  double a = 1.7976931348623157e+154;
  double b = 1.7976931348623157e+154;
  double c = 1.7976931348623157e+153;

  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 2);
}
END_TEST

START_TEST(test0_err3) {
  double a = 2;
  double b = 2;
  double c = 2;

  double complex *x1 = NULL, *x2 = NULL;
  int err = solve_equation(a, b, c, x1, x2);

  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(test0) {
  double a = 1;
  double b = -9;
  double c = 20;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq(creal(x1), 5);
  ck_assert_double_eq(cimag(x1), 0);
  ck_assert_double_eq(creal(x2), 4);
  ck_assert_double_eq(cimag(x2), 0);
}
END_TEST

START_TEST(test1) {
  double a = 1;
  double b = -6;
  double c = 34;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  print_double_complex(x1);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq(creal(x1), 3);
  ck_assert_double_eq(cimag(x1), 5);
  ck_assert_double_eq(creal(x2), 3);
  ck_assert_double_eq(cimag(x2), -5);
}
END_TEST

START_TEST(test2) {
  double a = 1;
  double b = 0;
  double c = 0;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq(creal(x1), 0);
  ck_assert_double_eq(cimag(x1), 0);
  ck_assert_double_eq(creal(x2), 0);
  ck_assert_double_eq(cimag(x2), 0);
}
END_TEST

START_TEST(test3) {
  double a = 1000;
  double b = -1000;
  double c = 1000;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq(creal(x1), 0.5);
  ck_assert(fabs(0.866025 - cimag(x1)) < 0.000001); // 0.866025
  ck_assert_double_eq(creal(x2), 0.5);
  ck_assert(fabs(0.866025 + cimag(x2)) < 0.000001); // -0.866025
}
END_TEST

START_TEST(test4) {
  double a = 57;
  double b = 12;
  double c = 100;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 0);
  printf("%f", cimag(x1));
  ck_assert(fabs(0.1052631 + creal(x1)) < 0.000001); // -2/19
  ck_assert(fabs(1.320342 - cimag(x1)) < 0.000001);  // 0.866025
  ck_assert(fabs(0.1052631 + creal(x2)) < 0.000001); // -2/19
  ck_assert(fabs(1.320342 + cimag(x2)) < 0.000001);  // -0.866025
}
END_TEST

START_TEST(test10) {
  double a = 1;
  double b = DBL_TRUE_MIN;
  double c = DBL_TRUE_MIN;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test11) {
  double a = 1;
  double b = DBL_MIN;
  double c = DBL_MIN;
  double complex x1 = 0, x2 = 0;
  int err = solve_equation(a, b, c, &x1, &x2);

  ck_assert_int_eq(err, 0);
}
END_TEST

Suite *test_solve_equation(void) {
  Suite *s = suite_create(GREEN("test_solve_equation"));

  TCase *tc_err1 = tcase_create("err1");
  tcase_add_test(tc_err1, test0_err1);
  suite_add_tcase(s, tc_err1);

  TCase *tc_err2 = tcase_create("err2");
  tcase_add_test(tc_err2, test0_err2);
  suite_add_tcase(s, tc_err2);

  TCase *tc_err3 = tcase_create("err3");
  tcase_add_test(tc_err2, test0_err3);
  suite_add_tcase(s, tc_err3);

  TCase *tc_body = tcase_create("body");
  tcase_add_test(tc_body, test0);
  tcase_add_test(tc_body, test1);
  tcase_add_test(tc_body, test2);
  tcase_add_test(tc_body, test3);
  tcase_add_test(tc_body, test4);
  tcase_add_test(tc_body, test10);
  tcase_add_test(tc_body, test11);
  suite_add_tcase(s, tc_body);

  return s;
}
