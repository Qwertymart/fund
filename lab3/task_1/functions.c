#include "header.h"

int sum (int num1, int num2)
{
    int res = 0, carry = 0;
    res = num1 ^ num2; // складываем без учета переноса
    carry = (num1 & num2) << 1; // сдвигаем перенос на 1 бит

    while(carry)
    {
        int temp = res;
        res = res ^ carry;
        carry = (temp & carry) << 1;
    }
    return res;
}

int negative(int n)
{
    return sum(~n, 1); // ~реверс битов
}

int subtraction(int num1, int num2)
{
    return sum(num1, negative(num2));
}

void print_num(int flag, char * res, int count)
{
    printf("Result: ");
    if(flag) printf("-");

    for (int i = count - 1; i >= 0; i--)
    {
        printf("%c", res[i]);
    }
    printf("\n");
}

int multiply(int a, int b)
{
    int res = 0;
    while(b != 0)
    {
        if (b & 1)
        {
            res += sum(res, a);
        }
        a<<=1;
        b>>=1;
    }
    return res;
}

enum status convert_to_base(int num, int r, char** res, int* capacity)
{
    if (r < 1 || r > 5)
    {
        return INPUT_ERROR;
    }
    char* base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int count = 0;
    int f_negative;

    if (num < 0)
    {
        f_negative = 1;
        num = negative(num);
    }
    int mask, digit;

    do
    {
        if (count >= *capacity)
        {
            *capacity <<= 1;
            char* temp = (char *)realloc(*res, multiply(*capacity, (int)sizeof(char)));
            if(temp == NULL)
            {
                return MEMORY_ERROR;
            }
            *res = temp;

        }
        mask = subtraction((1 << r), 1);
        digit = num & mask;
        (*res)[count] = base[digit];
        count = sum(count, 1);
        num >>= r;
    }
    while (num > 0);

    print_num(f_negative, *res, count);

    return SUCCESS;
}