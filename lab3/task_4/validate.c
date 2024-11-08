#include "header.h"

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int valid_date(int day, int month, int year, int hour, int minute, int second)
{
    if (day > 31 || day < 0)
    {
        return 0;
    }
    if (month > 12 || month < 0)
    {
        return 0;
    }
    if (year > 9999)
    {
        return 0;
    }
    if (hour >= 24 || hour < 0)
    {
        return 0;
    }
    if (minute > 60 || second > 60 || minute < 0 || second < 0)
    {
        return 0;
    }
    int days_in_month;
    switch (month) {
        case 4: case 6: case 9: case 11:
            days_in_month = 30;
            break;
        case 2:
            days_in_month = is_leap_year(year) ? 29 : 28;
            break;
        default:
            days_in_month = 31;
    }
    return day <= days_in_month;
}

int compare_date(int day1, int month1, int year1, int hour1, int minute1, int second1,
                  int day2, int month2, int year2, int hour2, int minute2, int second2)
{
    if (year1 != year2)
        return year1 < year2;
    if (month1 != month2)
        return month1 < month2;
    if (day1 != day2)
        return day1 < day2;
    if (hour1 != hour2)
        return hour1 < hour2;
    if (minute1 != minute2)
        return minute1 < minute2;
    return second1 < second2;
}


int is_valid_double(const char* str) {
    if (strlen(str) > 24){
        return 0;
    }
    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '.' && *p != '-' && *p != '+' && *p != 'e') {
            return 0;
        }
    }
    return 1;
}

int is_valid_int(const char* str)
{

    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '-' && *p != '+') {
            return 0;
        }
    }
    return 1;
}

int is_valid_date(const char* str)
{

    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p!=' ' && *p != ':' && *p != '\r' && *p != '\n') {
            return 0;
        }
    }
    return 1;
}

enum status str_to_int(const char *str, int * result)
{
    if (!(is_valid_int(str))){
        return INPUT_ERROR;
    }
    size_t len = strlen(str);
    if (len > 11 || (len == 11 && str[0] == '-' && str[1] > '2') || (len == 10 && str[0] != '-')) {
        return OVERFLOW;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, 10);

    if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
}

enum status str_to_double(char* str, double* result){

    if (!(is_valid_double(str))){
        return INPUT_ERROR;
    }
    if (strlen(str) > 17)
    {
        return OVERFLOW;
    }
    char *endptr;
    *result = strtod(str, &endptr);
    if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    return SUCCESS;
}