#include "date_func.h"

double GetTimeDiff(std::tm start, std::tm fin) {
    std::time_t x = std::mktime(&start);
    std::time_t y = std::mktime(&fin);
    return std::difftime(y, x) / (60 * 60 * 24);
}

int GetDaysInYearQua(std::tm date) {
    if (date.tm_year % 400 == 0)
        return 366;
    else if (date.tm_year % 100 == 0)
        return 365;
    else if (date.tm_year % 4 == 0)
        return 366;
    else
        return 365;
}

int GetDaysInMonthQua(std::tm date) {
    if(date.tm_mon == 0 || date.tm_mon == 2 || date.tm_mon == 4 || date.tm_mon == 6 || date.tm_mon == 7 || date.tm_mon == 9 || date.tm_mon == 11)
            return 31;
        else if(date.tm_mon == 3 || date.tm_mon == 5 || date.tm_mon == 8 || date.tm_mon == 10)
            return 30;
        else {
            if (GetDaysInYearQua(date) == 366)
                return 29;
            else
                return 28;
        }
        
}
