#include "header.h"

int main()
{
    double res1, res2, res3, res4;

    enum root f = dichotomy(&res1, func1, 1, 2, 0.0001);
    if (f == INPUT_ERROR)
    {
        printf("Input error\n");
    }
    else if (f == NO)
    {
        printf("The function has no root on the interval\n");
    }
    else if (f == YES)
    {
        printf("root: %lf\n", res1);
    }


    enum root f2 = dichotomy(&res2, func2, 3, 4, 0.0001);
    if (f2 == INPUT_ERROR)
    {
        printf("Input error\n");
    }
    else if (f2 == NO)
    {
        printf("The function has no root on the interval\n");
    }
    else if (f2 == YES)
    {
        printf("root: %lf\n", res2);
    }


    enum root f3 = dichotomy(&res3, func3, 1, 2, 0.0001);
    if (f3 == INPUT_ERROR)
    {
        printf("Input error\n");
    }
    else if (f3 == NO)
    {
        printf("The function has no root on the interval\n");
    }
    else if (f3 == YES)
    {
        printf("root: %lf\n", res3);
    }

    enum root f4 = dichotomy(&res4, func4, 1, 2, 0.0001);
    if (f4 == INPUT_ERROR)
    {
        printf("Input error\n");
    }
    else if (f4 == NO)
    {
        printf("The function has no root on the interval\n");
    }
    else if (f4 == YES)
    {
        printf("root: %lf\n", res4);
    }

    return 0;

}