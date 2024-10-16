#include "header.h"

int main(){
    int n1, n2, n3;
    oversscanf("100011 MC   -1b", "%Zr %Ro   %Cv", &n1, &n2, &n3, 11);
    printf("%d %d %d\n", n1, n2, n3);

    long int n;
    int f;
    oversscanf("11111", "%ld", &n);
    printf("%ld\n", n);

    FILE * file = fopen("1.txt", "r");
    int c;
    overfscanf(file, "%Ro", &c);
    printf("%d\n", c);
    fclose(file);
}
