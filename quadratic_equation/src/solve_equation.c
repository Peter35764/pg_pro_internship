#include <complex.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_equation.h"

int solve_equation(double a, double b, double c, double complex *x1,
                   double complex *x2) {
  int err = 0;

  if (fabs(a) < EPS) {
    err = 1;
#ifndef SILENT_MODE
    fprintf(stderr, "\tERROR: equation is not quadratic\n");
#endif
  } else if (!x1 || !x2) {
    err = 3;
#ifndef SILENT_MODE
    fprintf(stderr, "\tERROR: x1 or x2 are NULL pointers.\n");
#endif
  } else {
    long double la = a, lb = b, lc = c;
    long double complex ans1 = 0, ans2 = 0;

    long double det = lb * lb - 4 * la * lc;

    if (fabsl(det) < EPS) {
      ans1 = ans2 = -1 * lb / (2 * la);
    } else {
      ans1 = (-1 * lb + csqrt(det)) / (2 * la);
      ans2 = (-1 * lb - csqrt(det)) / (2 * la);
    }

    if (overflow_test_double(ans1) || overflow_test_double(ans2)) {
#ifndef SILENT_MODE
      fprintf(stderr, "\tERROR: overflow of variables.\n");
#endif
      err = 2;
    } else {
      *x1 = (double complex)ans1;
      *x2 = (double complex)ans2;
    }
  }

  return err;
}

int overflow_test_double(long double complex x) {
  return creall(x) > DBL_MAX || creall(x) < -1 * DBL_MAX ||
         cimagl(x) > DBL_MAX || cimagl(x) < -1 * DBL_MAX;
}

void print_double_complex(double complex x) {
  if (fabs(cimag(x)) < EPS) {
    printf("%.2f\n", creal(x));
  } else if (cimag(x) < 0) {
    printf("%.2f%.2fi\n", creal(x), cimag(x));
  } else {
    printf("%.2f+%.2fi\n", creal(x), cimag(x));
  }
}
