#include "header.h"

enum status add_mail(Post *post, Mail mail)
{
    if (post->mails == NULL)
    {
        post->mails = (Mail*) malloc(sizeof(Mail) * 1);
        if (post->mails)
        {
            post->mail_count = 1;
            post->mails[0] = mail;
        }
    }
    else
    {
        Mail *temp = (Mail *)realloc(post->mails, (post->mail_count + 1) * sizeof(Mail));
        if (temp)
        {
            post->mails = temp;
            post->mails[post->mail_count++] = mail;
        }
        else
        {
            delete_mail(post, NULL);
            return MEMORY_ERROR;
        }

    }
    return SUCCESS;
}

void delete_mail(Post *post, const char* id)
{
    if (id == NULL)
    {
        for (int i = 0; i < post->mail_count; ++i)
        {
            delete_string(&post->mails[i].id);
            delete_string(&post->mails[i].creation_time);
            delete_string(&post->mails[i].delivery_time);
            post->mails[i] = post->mails[post->mail_count - 1];
            post->mail_count--;
        }
    }
    else
    {
        for (int i = 0; i < post->mail_count; ++i)
        {
            if (strcmp(post->mails[i].id.data, id) == 0)
            {
                delete_string(&post->mails[i].id);
                delete_string(&post->mails[i].creation_time);
                delete_string(&post->mails[i].delivery_time);
                post->mails[i] = post->mails[post->mail_count - 1];
                post->mail_count--;
                return;
            }
        }
        printf("Mail with ID %s not found.\n", id);
    }
}

Mail create_mail(Address recipient, double weight, char* id,
                 char* creation_time, char* delivery_time)
{
    Mail mail;
    mail.recipient = recipient;
    mail.weight = weight;
    mail.id = create_string(id);
    mail.creation_time = create_string(creation_time);
    mail.delivery_time = create_string(delivery_time);
    return mail;
}

int compare_mail(const void* a, const void* b)
{
    Mail *mail_1 = (Mail *)a;
    Mail *mail_2 = (Mail *)b;
    int postal;
    if ((postal = strcmp(mail_1->recipient.postal_code.data, mail_2->recipient.postal_code.data)) != 0)
    {
        return postal;
    }
    return strcmp(mail_1->id.data, mail_2->id.data);
}

void sort_mails(Post* post)
{
    qsort(post->mails, post->mail_count, sizeof(Mail), compare_mail);
}

void print_mail(const Mail *mail) {
    printf("ID: %s\nRecipient: %s, %s, House: %d, Building: %s, Apartment: %d\nWeight: %.2f\nCreation time: %s\nDelivery time: %s\n\n",
           mail->id.data, mail->recipient.city.data, mail->recipient.street.data,
           mail->recipient.house, mail->recipient.building.data, mail->recipient.apartment,
           mail->weight, mail->creation_time.data, mail->delivery_time.data);
}

void find_mail_by_id(const Post* post, const char *id)
{
    for (int i = 0; i < post->mail_count; ++i)
    {
        if (strcmp(post->mails[i].id.data, id) == 0)
        {
            print_mail(&post->mails[i]);
            return;
        }
    }
    printf("Mail with ID %s not found.\n", id);
}


int parse_time(const char* time, struct tm *tm_time, time_t* t)
{
    int f = sscanf(time, "%2d:%2d:%4d %2d:%2d:%2d",
                   &tm_time->tm_mday, &tm_time->tm_mon, &tm_time->tm_year,
                   &tm_time->tm_hour, &tm_time->tm_min, &tm_time->tm_sec) == 6;

    tm_time->tm_mon -= 1;
    tm_time->tm_year -= 1900;
    tm_time->tm_isdst = -1;

    *t = mktime(tm_time);

    return f;
}

void list_delivered_mail(const Post* post)
{
    time_t now = time(NULL), delivery_time;
    struct tm tm;

    for (int i = 0; i < post->mail_count; ++i)
    {
        if (parse_time(post->mails[i].delivery_time.data, &tm, &delivery_time))
        {
            if (now > delivery_time)
            {
                printf("Expired Mail: ID: %s, Creation time: %s, Delivery time: %s\n",
                       post->mails[i].id.data, post->mails[i].creation_time.data, post->mails[i].delivery_time.data);
            }
        }
    }
}

void list_not_delivered_mail(const Post* post)
{
    time_t now = time(NULL), delivery_time;
    struct tm tm;

    for (int i = 0; i < post->mail_count; ++i)
    {
        if (parse_time(post->mails[i].delivery_time.data, &tm, &delivery_time))
        {
            if (now < delivery_time)
            {
                printf("Not Expired Mail: ID: %s, Creation time: %s, Delivery time: %s\n",
                       post->mails[i].id.data, post->mails[i].creation_time.data, post->mails[i].delivery_time.data);
            }
        }
    }
}
