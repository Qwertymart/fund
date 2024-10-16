#include "header.h"

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int has_finite_representation(double value, int base)
{
    int denominator = 1;

    while(fabs(value - (int)value) > EPS)
    {
        if (value > DBL_MAX / 10)
        {
            return DOESNT_FINITE_REPRESENTATION;
        }
        value *= 10;
        denominator *= 10;
    }

    int numerator = (int)value;
    int common_divisor = gcd(numerator, denominator);
    denominator /= common_divisor;

    for (int i = 2; i <= sqrt(denominator); ++i) {
        while (denominator % i == 0) {
            if (base % i != 0) {
                return DOESNT_FINITE_REPRESENTATION;
            }
            denominator /= i;
        }

    }
    if (denominator > 1 && base % denominator != 0) {
        return DOESNT_FINITE_REPRESENTATION;
    }

    return HAS_FINITE_REPRESENTATION;
}

void check_finite_representations(int base, int num_value, ...)
{
    va_list args;
    va_start(args, num_value);

    for (int i = 0; i < num_value; ++i)
    {
        double value = va_arg(args, double );
        if (has_finite_representation(value, base) == HAS_FINITE_REPRESENTATION) {
            printf("Число %.10f имеет конечное представление в системе счисления с основанием %d\n", value, base);
        } else {
            printf("Число %.10f не имеет конечного представления в системе счисления с основанием %d\n", value, base);
        }

    }
}
