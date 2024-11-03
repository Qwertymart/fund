#include "header.h"

void menu()
{
    printf("<=======================================================>\n"
           "Menu:\n"
           "line limit - 50 characters\n"
           "1. Sort by id\n"
           "2. Sort by first name\n"
           "3. Sort by last name\n"
           "4. Sort by group\n"
           "5. Outputting student information to a out_file (id)\n"
           "6. Output to a out_file information about a student whose average score is higher than the rest\n"
           "7. Clear output file\n"
           "8. Exit\n"
           "<=======================================================>\n");
}
int main(int argc, char* argv[])
{
   if (argc != 3)
   {
       printf("Input error\n");
       return INPUT_ERROR;
   }
    char* ind1 = strrchr(argv[1], '/');
    char* ind2 = strrchr(argv[2], '/');
    int index_1 = 0, index_2 = 0;

    if (ind1 != NULL) index_1 = ind1 - argv[1] + 1;
    if (ind2 != NULL) index_2 = ind2 - argv[2] + 1;

    if (strcmp(argv[1] + index_1, argv[2] + index_2) == 0){
        printf("Identical file names\n");
        return INPUT_ERROR;
    }
   FILE* input = fopen(argv[1], "r");
   if (input == NULL)
   {
       printf("Error opening\n");
       return INPUT_ERROR;
   }
   Student *students = NULL;
   int size, capacity;
   if (read_from_file(input, &students, &size, &capacity) != SUCCESS)
   {
       printf("Input Error\n");
       free(students);
       fclose(input);
       return INPUT_ERROR;
   }
    fclose(input);
    print_array(students, size);
    char choice[3];
    int flag = 1;
    while (flag)
    {
        menu();
        printf("Your choice: ");
        if (fgets(choice, sizeof(choice), stdin) == NULL)
        {
            flag = 0;
            continue;
        }
        choice[strcspn(choice, "\n")] = '\0';
        if (strlen(choice) != 1)
        {
            printf("Invalid choice. Try again.\n");
            continue;
        }
        switch (choice[0])
        {
            case '1':
            {
                qsort(students, size, sizeof(Student), compare_id);
                printf("Array sorted by id\n");
                print_array(students, size);
                break;
            }
            case '2':
            {
                qsort(students, size, sizeof(Student), compare_name);
                printf("Array sorted by name\n");
                print_array(students, size);
                break;
            }
            case '3':
            {
                qsort(students, size, sizeof(Student), compare_surname);
                printf("Array sorted by surname\n");
                print_array(students, size);
                break;
            }
            case '4':
            {
                qsort(students, size, sizeof(Student), compare_group);
                printf("Array sorted by group\n");
                print_array(students, size);
                break;
            }
            case '5':
            {
                printf("Searched ID: ");
                int search_id;
                int temp = scanf("%d", &search_id);
                char c;
                while ((c = getchar()) != '\n' && c != EOF);
                if (temp != 1)
                {
                    break;
                }
                int found = 0;
                for(int i = 0; i < size; ++i)
                {
                    if (students[i].id == search_id)
                    {
                        FILE* output = fopen(argv[2], "a");
                        if (output == NULL)
                        {
                            printf("Error opening\n");
                            break;
                        }
                        fprintf(output, "%d %s %s %s %lf\n", students[i].id,
                                students[i].name, students[i].surname, students[i].group,
                                students[i].average_score);
                        printf("Recording successful\n");
                        fclose(output);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    printf("ID not found\n");
                }
                break;
            }
            case '6':
            {
                qsort(students, size, sizeof(Student), compare_score);

                FILE *output = fopen(argv[2], "a");
                if (output == NULL)
                {
                    printf("Error opening output file\n");
                    break;
                }
                double average_score_all = 0;

                for(int i = 0; i < size; ++i)
                {
                    average_score_all += students[i].average_score;
                }
                average_score_all /= size;

                for (int i = 0; i < size; ++i)
                {
                    if (students[i].average_score > average_score_all)
                    {
                        fprintf(output,"%d %s %s %s %c %c %c %c %c\n",
                                students[i].id, students[i].name, students[i].surname,
                                students[i].group, students[i].marks[0],
                                students[i].marks[1], students[i].marks[2],
                                students[i].marks[3], students[i].marks[4]);
                    }
                    else break;
                }
                printf("Entry made\n");
                fclose(output);
                break;
            }
            case '7':
            {
                FILE *output = fopen(argv[2], "w");
                fclose(output);
                printf("File cleared\n");
                break;
            }
            case '8':
            {
                flag = 0;
                break;
            }
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
    free(students);
    return 0;
}