#include "header.h"

void display_menu() {
    printf("\nChoose an action:\n");
    printf("1. Add a new mail\n");
    printf("2. Delete mail by ID\n");
    printf("3. Find mail by ID\n");
    printf("4. Show delivered mails\n");
    printf("5. Show undelivered mails\n");
    printf("6. Exit\n");
    printf("Your choice: ");
}

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Post post;
    post.post_office_address = (Address *)malloc(sizeof(Address));

    int choice;
    char id[16];
    char city[51], street[51], building[11], postal_code[11];
    int house_number, apartment;
    double weight;
    char creation_time[21], delivery_time[21];

    while (1) {
        display_menu();
        scanf("%d", &choice);
        flush_input();

        switch (choice) {
            case 1:
                // Add new mail
                printf("Enter details for the new mail.\n");

                printf("Recipient's city: ");
                scanf("%51s", city);
                flush_input();
                if (strlen(city) > 50)
                {
                    printf("City is too long\n");
                    break;
                }

                printf("Street: ");
                scanf("%51s", street);
                flush_input();
                if (strlen(street) > 50)
                {
                    printf("Street is too long\n");
                    break;
                }

                char temp_house[15];
                printf("House number: ");
                scanf("%15s", temp_house);
                flush_input();
                if (str_to_int(temp_house, &house_number) != SUCCESS)
                {
                    printf("House number is too long or write incorrectly\n");
                    break;
                }

                printf("Building: ");
                scanf("%10s", building);
                flush_input();
                if (strlen(building ) > 9)
                {
                    printf("Building is too long\n");
                    break;
                }

                char temp_apartment[15];
                printf("Apartment number: ");
                scanf("%15s", temp_apartment);
                flush_input();
                if (str_to_int(temp_apartment, &apartment) != SUCCESS)
                {
                    printf("Apartment is too long or write incorrectly\n");
                    break;
                }

                printf("Postal code: ");
                scanf("%10s", postal_code);
                flush_input();
                if (strlen(postal_code) > 9)
                {
                    printf("Postal code is too long\n");
                    break;
                }

                char temp_weight[20];
                printf("Weight: ");
                scanf("%20s", temp_weight);
                flush_input();
                if (str_to_double(temp_weight, &weight) != SUCCESS)
                {
                    printf("Weight is too long or write incorrectly\n");
                    break;
                }

                printf("Mail ID (14 digits): ");
                scanf("%15s", id);
                flush_input();
                if (strlen(id) != 14)
                {
                    printf("Id is written incorrectly\n");
                    break;
                }

                int creation_day, creation_month, creation_year,
                creation_hour, creation_minute, creation_second;

                printf("Creation time (dd:MM:yyyy hh:mm:ss): ");
                if (scanf("%d:%d:%d %d:%d:%d", &creation_day, &creation_month, &creation_year, &creation_hour, &creation_minute, &creation_second) != 6)
                {
                    printf("Input error\n");
                    break;
                }
                if (!valid_date(creation_day, creation_month, creation_year, creation_hour, creation_minute, creation_second)) {
                    printf("Data incorrectly\n");
                    break;
                }
                sprintf(creation_time, "%02d:%02d:%04d %02d:%02d:%02d", creation_day, creation_month, creation_year, creation_hour, creation_minute, creation_second);
                flush_input();

                int delivery_day, delivery_month, delivery_year,
                        delivery_hour, delivery_minute, delivery_second;

                char buffer[50];
                printf("Delivery time (dd:MM:yyyy hh:mm:ss): ");
                if (fgets(buffer, sizeof(buffer), stdin) != NULL)
                {
                    if (sscanf(buffer, "%d:%d:%d %d:%d:%d",
                               &delivery_day, &delivery_month, &delivery_year,
                               &delivery_hour, &delivery_minute, &delivery_second) != 6) {
                        printf("Input error\n");
                        break;
                    }
                }
                else
                {
                    printf("Input error\n");
                    break;
                }
                if (!valid_date(delivery_day, delivery_month, delivery_year, delivery_hour, delivery_minute, delivery_second)) {
                    printf("Data incorrectly\n");
                    break;
                }
                sprintf(delivery_time, "%02d:%02d:%04d %02d:%02d:%02d", delivery_day, delivery_month, delivery_year, delivery_hour, delivery_minute, delivery_second);

                if (!compare_date(creation_day, creation_month, creation_year, creation_hour, creation_minute, creation_second,
                                   delivery_day, delivery_month, delivery_year, delivery_hour, delivery_minute, delivery_second)) {
                    printf("Creation date is not earlier than delivery date\n");
                    break;
                }


                Address recipient = {create_string(city), create_string(street), house_number, create_string(building), apartment, create_string(postal_code)};
                Mail new_mail = create_mail(recipient, weight, id, creation_time, delivery_time);
                add_mail(&post, new_mail);
                sort_mails(&post);
                printf("Mail added and sorted.\n");
                break;

            case 2:
                // Delete mail by ID
                printf("Enter the ID of the mail to delete: ");
                scanf("%14s", id);
                delete_mail(&post, id);
                printf("Mail with ID %s deleted.\n", id);
                break;

            case 3:
                // Find mail by ID
                printf("Enter the ID of the mail to search: ");
                scanf("%14s", id);
                find_mail_by_id(&post, id);
                break;

            case 4:
                // Show delivered mails
                printf("List of delivered mails:\n");
                list_delivered_mail(&post);
                break;

            case 5:
                // Show expired mails
                printf("List of undelivered mails:\n");
                list_not_delivered_mail(&post);
                break;

            case 6:
                // Exit
                printf("Exiting the program.\n");
                for (int i = 0; i < post.mail_count; i++) {
                    delete_string(&post.mails[i].id);
                    delete_string(&post.mails[i].creation_time);
                    delete_string(&post.mails[i].delivery_time);
                    delete_string(&post.mails[i].recipient.city);
                    delete_string(&post.mails[i].recipient.street);
                    delete_string(&post.mails[i].recipient.building);
                    delete_string(&post.mails[i].recipient.postal_code);
                }
                free(post.mails);
                delete_string(&post.post_office_address->city);
                delete_string(&post.post_office_address->street);
                delete_string(&post.post_office_address->building);
                delete_string(&post.post_office_address->postal_code);
                free(post.post_office_address);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
