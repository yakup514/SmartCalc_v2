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
    void SetData(double summ, int term, std::tm start, double rate, bool type) noexcept;
};

#endif // CREDITMODEL_H
