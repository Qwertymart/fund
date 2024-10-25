#include "header.h"

int main(){
    int n1, n2, n3;
    oversscanf("100011 MC   -1b", "%Zr %Ro   %Cv", &n1, &n2, &n3, 11);
    printf("%d %d %d\n", n1, n2, n3);

    char * n =NULL;
    int f;
    oversscanf("NULL ", "%5s ", &n);
    printf("%s\n", n);

    FILE * file = fopen("1.txt", "r");
    int c;
    overfscanf(file, "%5s", NULL);
    printf("%d\n", c);
    fclose(file);
}
