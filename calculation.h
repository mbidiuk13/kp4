#ifndef CALCULATION_H
#define CALCULATION_H
#include <math.h>
#define M_PI 3.14159265358979323846
#define TO_DEGREES(radian) ((radian) * 180.0 / M_PI)

double taylor_sin(double x, double epsilon)
{
    double term = x, result = term;
    unsigned n = 1;

    do
    {
        term *= -x * x / (double)((n + 2) * (n + 1));
        result += term;
        n += 2;
    }
    while (fabs(term) > epsilon);

    return result;
}

double taylor_cos(double x, double epsilon)
{
    double term = 1, result = term;
    unsigned n = 1;

    do
    {
        term *= -x * x / (double)(2 * n * (2 * n - 1));
        result += term;
        n++;
    }
    while (fabs(term) > epsilon);

    return result;
}

#endif
