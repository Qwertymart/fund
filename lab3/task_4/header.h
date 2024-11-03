#ifndef FUND__HEADER_H
#define FUND__HEADER_H

enum status{
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO, NOT_FOUND,
    MEMORY_ERROR, OVERFLOW
};
#include <ctype.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include "string.h"
#include "float.h"
#include <stdarg.h>
#include <time.h>
typedef struct
{
    char* data;
    int lenght;
}String;

typedef struct
{
    String city;
    String street;
    int house;
    String building;
    int apartment;
    String postal_code;
}Address;

typedef struct
{
    Address recipient;
    double weight;
    String id;
    String creation_time;
    String delivery_time;

}Mail;

typedef struct {
    Address *post_office_address;
    Mail *mails;
    int mail_count;
} Post;

void delete_string(String* str);
String create_string(const char* input);
int compare_string(String* str_1, String* str_2);
int equals_string(String* str_1, String* str_2);
void copy_string(String* str_1, String* str_2);
String duplicate_string(String* str);
void concat_string(String* str_1, String* str_2);

void add_mail(Post *post, Mail mail);
void delete_mail(Post *post, const char* id);
Mail create_mail(Address recipient, double weight, char* id,
                 char* creation_time, char* delivery_time);
int compare_mail(const void* a, const void* b);
void sort_mails(Post* post);
void find_mail_by_id(const Post* post, const char *id);
void list_delivered_mail(const Post* post);
int parse_time(const char* time, struct tm *tm_time, time_t* t);
void list_not_delivered_mail(const Post* post);

enum status str_to_int(const char *str, int * result);
enum status str_to_double(char* str, double* result);
int valid_date(int day, int month, int year, int hour, int minute, int second);
int compare_date(int day1, int month1, int year1, int hour1, int minute1, int second1,
                 int day2, int month2, int year2, int hour2, int minute2, int second2);



#endif //FUND__HEADER_H
