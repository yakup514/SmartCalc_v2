#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <vector>
#include <iostream>
#include <cmath>
#include "date_func.h"
#include <ctime>
class CreditModel{
    double summ_;
    int term_;
    std::tm start_;
    double rate_;
    bool type_anyit_;
   
    
public:
    CreditModel();
    std::vector<std::tm> time_;
    std::vector<double> per_paid_;
    std::vector<double> main_debt_paid_;
    std::vector<double> month_paid_;
    std::vector<double> rem_debt_;
    void SetData(double summ, int term, std::tm start, double rate, bool type) noexcept;
    void ClearData() noexcept;
    double Calculate();
    double GetPercSumm() {
        double res = 0;
        for (auto v : per_paid_)
            res += v;
        return res;
    }
};

#endif // CREDITMODEL_H
