#include "header.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Incorrect count arguments\n");
        return INPUT_ERROR;
    }
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Error open file %s\n", argv[1]);
        return INPUT_ERROR;
    }

    int count = 0, capacity = 10;
    Employee* employees =(Employee *) malloc(capacity * sizeof(Employee));
    if (employees == NULL)
    {
        printf("Memory error\n");
        fclose(input_file);
        return MEMORY_ERROR;
    }

    Employee temp;
    int flag;
    char name_temp[51], surname_temp[51], id_temp[15], salary_temp[20];
    while((flag = fscanf(input_file, "%s %s %s %s", id_temp, name_temp, surname_temp, salary_temp)) != EOF)
    {
        if (flag == 4)
        {
            if(str_to_int(id_temp, &temp.id) != SUCCESS)
            {
                printf("Id is to long or write incorrectly\n");
                free(employees);
                fclose(input_file);
                return INPUT_ERROR;
            }
            if (str_to_double(salary_temp, &temp.salary) != SUCCESS)
            {
                printf("Salary is to long or write incorrectly\n");
                free(employees);
                fclose(input_file);
                return INPUT_ERROR;
            }
            if (strlen(name_temp) > 50 || strlen(surname_temp) > 50)
            {
                printf("Name or surname is too long\n");
                free(employees);
                fclose(input_file);
                return INPUT_ERROR;
            }
            strcpy(temp.name, name_temp);
            strcpy(temp.surname, surname_temp);

            if (count >= capacity) {
                capacity *= 2;
                Employee *employees_realloc = realloc(employees, capacity * sizeof(Employee));
                if (employees_realloc == NULL)
                {
                    printf("Memory error\n");
                    fclose(input_file);
                    free(employees);
                    return MEMORY_ERROR;
                }
                employees = employees_realloc;
            }
            employees[count++] = temp;
        }
        else
        {
            printf("Input file format error\n");
            free(employees);
            fclose(input_file);
            return INPUT_ERROR;
        }
    }
    fclose(input_file);

    if (argv[2][0] != '-' && argv[2][0] != '/')
    {
        printf("Input error\n");
        free(employees);
        return INPUT_ERROR;
    }
    else
    {
        if (argv[2][1] == 'a')
        {
            qsort(employees, count, sizeof(Employee), cmp_a);
        }
        else if (argv[2][1] == 'd')
        {
            qsort(employees, count, sizeof(Employee), cmp_d);
        }
        else
        {
            printf("Incorrect flag\n");
            free(employees);
            return INPUT_ERROR;
        }
    }

    FILE * out_file = fopen(argv[3], "w");
    if (out_file == NULL)
    {
        printf("Error open file\n");
        free(employees);
        return INPUT_ERROR;
    }
    for (int i = 0; i < count; i++) {
        fprintf(out_file, "%d %s %s %.2f\n", employees[i].id, employees[i].name, employees[i].surname, employees[i].salary);
    }
    fclose(out_file);
    free(employees);
    printf("Success\n");
    return SUCCESS;
}
