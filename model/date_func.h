//
//  date_func.h
//  smartCalcv2
//
//  Created by mcbk on 28.09.2023.
//

#ifndef date_func_h
#define date_func_h
#include <ctime>
double GetTimeDiff(std::tm start, std::tm fin) ;

int GetDaysInYearQua(std::tm date) ;

int GetDaysInMonthQua(std::tm date) ;

#endif /* date_func_h */
