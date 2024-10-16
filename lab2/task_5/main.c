#include "header.h"

int main() {


    long long t = 999999999;
    overfprintf(stdout, "//%%1%%%05d", 1);



    char Ro[64];
    oversprintf(Ro, "%Zr \n", 9999999999999999999);
    printf("Ro: %s\n", Ro);


    char Zr[64];
    oversprintf(Zr, "%Zr", 11);
    printf("Zr: %s\n", Zr);


    char Cv[64];
    oversprintf(Cv, "%Cv", 155, 16);
    printf("Cv: %s\n", Cv);

    char CV[64];
    oversprintf(CV, "%CV", 155, 16);
    printf("CV: %s\n", CV);

    char to[64];
    oversprintf(to, "%to", "-1a", 11);
    printf("to: %s\n", to);

    char TO[64];
    oversprintf(TO, "%TO", "1B", 12);
    printf("TO: %s\n", TO);

    char mi[64];
    oversprintf(mi, "%mi", 5);
    printf("mi : %s\n", mi);

    char mu[64];
    unsigned int x = 5;
    oversprintf(mu, "%mu", x);
    printf("mu : %s\n", mu);

    char md[64];
    double x1 = 5.111111111;
    oversprintf(md, "%md", x1);
    printf("md : %s\n", md);

    char mf[64];
    double x2 = 5.11111;
    oversprintf(mf, "%mf", x2);
    printf("mf : %s\n", mf);

    char l[64];
    oversprintf(l, "%f", 0.1);
    printf("%s\n", l);


///////////////////////////////////////////////////////////////////////


    FILE *file = fopen("test.txt", "w"); // Открываем файл для записи
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    overfprintf(file, "Ro: %Ro", 13);
    overfprintf(file, "\n");
    overfprintf(file, "Zr: %Zr", 13);
    overfprintf(file, "\n");
    overfprintf(file, "Cv: %Cv", 155, 16);
    overfprintf(file, "\n");
    overfprintf(file, "CV: %CV", 155, 16);
    overfprintf(file, "\n");
    overfprintf(file, "to: %to", "-1a", 11);
    overfprintf(file, "\n");
    overfprintf(file, "TO: %TO", "1B", 12);
    overfprintf(file, "\n");

    overfprintf(file, "mi: %mi", 5);
    overfprintf(file, "\n");

    overfprintf(file, "mu: %mu", x);
    overfprintf(file, "\n");

    overfprintf(file, "md: %md", x1);
    overfprintf(file, "\n");

    overfprintf(file, "mf: %mf", x2);
    overfprintf(file, "\n");

    overfprintf(file, "%f", 0.1);
    overfprintf(file, "\n");

    fclose(file);
    return 0;
}