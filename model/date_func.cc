#include "date_func.h"

double GetTimeDiff(std::tm start, std::tm fin) {
    std::tm tmp1{}, tmp2{};
    tmp1.tm_mday = start.tm_mday;
    tmp1.tm_mon = start.tm_mon;
    tmp1.tm_year = start.tm_year;
    tmp2.tm_mday = fin.tm_mday;
    tmp2.tm_mon = fin.tm_mon;
    tmp2.tm_year = fin.tm_year;
    std::time_t x = std::mktime(&tmp1);
    std::time_t y = std::mktime(&tmp2);
    return std::difftime(y, x) / (60 * 60 * 24);
}

int GetDaysInYearQua(std::tm date) {
    if ((date.tm_year + 1900) % 400 == 0)
        return 366;
    else if ((date.tm_year + 1900) % 100 == 0)
        return 365;
    else if ((date.tm_year + 1900) % 4 == 0)
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
