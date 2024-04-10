#include <stdio.h>

#include "../src/quadratic_equation.h"

int main(void) {
  printf("Решения уравнения x^2 - 9x + 20:\n");
  double a = 1;
  double b = -9;
  double c = 20;
  double complex x1 = 0, x2 = 0;

  int err = solve_equation(a, b, c, &x1, &x2);

  print_double_complex(x1);
  print_double_complex(x2);
  printf("Код ошибки: %d, %s\n", err,
         err == 0 ? GREEN("ошибки не возникло!") : RED("ошибка возникла!"));

  return 0;
}
