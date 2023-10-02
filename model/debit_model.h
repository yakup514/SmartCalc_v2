#ifndef DEBITMODEL_H
#define DEBITMODEL_H

#include "date_func.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
class DebitModel {
    double summ_;
    int term_;
    std::tm start_;
    double rate_;
    int kap_per_;
    bool kapitalization_;
    bool curr_is_rub_;
    double deposit_rep_;
    int deposit_rep_term_;
   
   // double GetTimeDiff(std::tm start, std::tm fin);
//    double GetDaysInYearQua(std::tm date);
    double GetPersEarnedByPeriod(double rate, std::tm fin);
//    int GetDaysInMonthQua(std::tm date);
    std::vector<std::tm> time_;
    
public:
    DebitModel();
    DebitModel(double summ, int term, std::tm start, double rate, int kap_per, bool kapitalization, bool curr_is_rub, double deposit_rep, int deposit_rep_term);
    void SetData(double summ, int term, std::tm start, double rate, int kap_per, bool kapitalization, bool curr_is_rub, double deposit_rep, int deposit_rep_term);
    std::vector<double> perc_acc_;
    std::vector<double> tax_paid_;
    std::vector<double> perc_paid_;
    std::vector<double> summ_end_per_;
    std::vector<double> dep_rep_sum_;
    std::vector<std::tm> output_time_;
    void Calculate();
    double GetResult();
    double GetDepositRepSumm() {return GetVectorSumm(dep_rep_sum_);};
    double GetPercentSumm();
    double GetTaxSumm(){return GetVectorSumm(tax_paid_);};
    double GetVectorSumm(const std::vector<double>& data);
    void DataClear();
    
};

#endif // DEBITMODEL_H
