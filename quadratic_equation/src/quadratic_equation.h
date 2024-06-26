#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include <complex.h>
#define EPS 1e-7

#define GREEN(str) "\033[32;1;2m" str "\033[0m"
#define RED(str) "\033[31;1;2m" str "\033[0m"

// Закомментируйте строку для вывода дополнительной информации об
// ошибках в stderr.
#define SILENT_MODE

/**
 * @brief Решает квадратное уравнение вида ax^2 + bx + c = 0.
 *
 * Вычислить корни квадратного уравнения с помощью квадратного корня.
 * Если уравнение не является квадратным (a = 0), возвращается ошибка.
 * Если корни слишком большие, чтобы быть представленными как double,
 * возвращается ошибка.
 *
 * @param a Коэффициент при квадратном члене.
 * @param b Коэффициент при линейном члене.
 * @param c Константный член.
 * @param x1 Указатель для хранения первого корня уравнения.
 * @param x2 Указатель для хранения второго корня уравнения.
 * @return Целое число, представляющее код ошибки:
 *         - 0, если уравнение было успешно решено.
 *         - 1, если уравнение не является квадратным.
 *         - 2, если происходит переполнение переменных.
 *         - 3, если переменные x1 или x2 это NULL указатели.
 */
int solve_equation(double a, double b, double c, double complex *x1,
                   double complex *x2);

/**
 * @brief Проверяет, превышает ли вещественная и мнимая части числа double
 * максимальное значение double.
 *
 * Функция проверяет, превышает ли вещественная и мнимая части числа double
 * максимальное значение double, определенное как DBL_MAX. Если превышение
 * происходит, возвращается 1, иначе 0.
 *
 * @param x Комплексное число типа long double.
 * @return 1, если превышение обнаружено, иначе 0.
 */
int overflow_test_double(long double complex x);

/**
 * @brief Выводит комплексное число типа double на стандартный вывод.
 *
 * @param x Комплексное число типа double.
 */
void print_double_complex(double complex x);

#endif // QUADRATIC_EQUATION_H
