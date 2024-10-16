#include "header.h"

int main()
{
    double n = 1./3.;

    check_finite_representations(2, 4, 0.25, 0.125, 0.3, 0.75);
    check_finite_representations(2, 3, 0.1, n, 0.5);

    check_finite_representations(10, 4, 0.1, 0.5, 0.25, 0.75);
    check_finite_representations(10, 2, n, 0.2);


    check_finite_representations(3, 3, 0.3, 0.6, 0.5);
    check_finite_representations(3, 3, 0.111111, 0.666666, 0);
}
