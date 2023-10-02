#include "debit_model.h"


DebitModel::DebitModel(){

}

DebitModel::DebitModel(double summ, int term, std::tm start, double rate, int kap_per, bool kapitalization, bool curr_is_rub, double deposit_rep, int deposit_rep_term) : summ_{summ}
                        , term_{term}
                        , start_{start}
                        , rate_(rate)
                        , kap_per_(kap_per)
                        , kapitalization_{kapitalization}
                        , curr_is_rub_{curr_is_rub}
                        , deposit_rep_{deposit_rep}
                        , deposit_rep_term_{deposit_rep_term} {
    time_.push_back(start_);
    output_time_.push_back(start_);
    summ_end_per_.push_back(summ_);
    perc_acc_.push_back(0);
    perc_paid_.push_back(0);
    tax_paid_.push_back(0);
    dep_rep_sum_.push_back(0);
}


void DebitModel::DataClear() {
    time_.clear();
    output_time_.clear();
    summ_end_per_.clear();
    perc_acc_.clear();
    perc_paid_.clear();
    tax_paid_.clear();
    dep_rep_sum_.clear();

}
void DebitModel::SetData(double summ, int term, std::tm start, double rate, int kap_per, bool kapitalization, bool curr_is_rub, double deposit_rep, int deposit_rep_term){
    DataClear();
    time_.push_back(start);
    output_time_.push_back(start);
    summ_end_per_.push_back(summ);
    perc_acc_.push_back(0);
    perc_paid_.push_back(0);
    tax_paid_.push_back(0);
    dep_rep_sum_.push_back(0);
    summ_ = summ;
    term_ = term;
    start_ = start;
    rate_ = rate;
    kap_per_ = kap_per;
    kapitalization_ = kapitalization;
    curr_is_rub_ = curr_is_rub;
    deposit_rep_ = deposit_rep;
    deposit_rep_term_ = deposit_rep_term;

}


double DebitModel::GetPersEarnedByPeriod(double rate, std::tm fin) {
    double perc_earned = 0;
    
    std::tm last_day = time_.back();
    last_day.tm_mday = GetDaysInMonthQua(time_.back());
    std::tm first_day = fin;
    first_day.tm_mday = 1;
    perc_earned = summ_end_per_.back() * (rate / 100.0) * ((GetTimeDiff(time_.back(), last_day) + 1)/ GetDaysInYearQua(time_.back()) + GetTimeDiff(first_day, fin) / GetDaysInYearQua(fin));
    
    
    
    return perc_earned;
}

void DebitModel::Calculate() {
    double perc_earned = 0;
    double tax = 0;
    for (int i = 1; i < term_ + 1; ++i) {

            std::tm tmp = start_;
            tmp.tm_mon = (start_.tm_mon + i) % 12;
            tmp.tm_year = (start_.tm_mon + i) / 12 + start_.tm_year;
            tmp.tm_mday = start_.tm_mday > GetDaysInMonthQua(tmp) ? GetDaysInMonthQua(tmp) : start_.tm_mday;
            
        if (curr_is_rub_ && rate_ > 18.0) {
            tax += (GetPersEarnedByPeriod(rate_, tmp) - GetPersEarnedByPeriod(18.0,  tmp)) * 0.35;
        } else if (!curr_is_rub_ && rate_ > 9) {
            tax += ((GetPersEarnedByPeriod(rate_,  tmp) - GetPersEarnedByPeriod(9.0,  tmp)) * 0.35);
        }
        perc_earned += GetPersEarnedByPeriod( rate_,  tmp);
        time_.push_back(tmp);
        if ((i % kap_per_ == 0 || i == term_ )) {
            if (kapitalization_) {
                perc_paid_.push_back(0);
                perc_acc_.push_back((perc_earned));
                if (i % deposit_rep_term_ == 0 && deposit_rep_ > 0 && i != term_) {
                    dep_rep_sum_.push_back(deposit_rep_);
                    summ_end_per_.push_back(summ_end_per_.back() + perc_earned - tax + deposit_rep_);
                } else {
                    dep_rep_sum_.push_back(0);
                    summ_end_per_.push_back(summ_end_per_.back()  + perc_earned - tax );
                }
            } else {
                perc_acc_.push_back(0);
                perc_paid_.push_back((perc_earned));
                if (i % deposit_rep_term_ == 0 && deposit_rep_ > 0 && i != term_) {
                    dep_rep_sum_.push_back(deposit_rep_);
                    summ_end_per_.push_back(summ_end_per_.back() + deposit_rep_);
                } else {
                    dep_rep_sum_.push_back(0);
                    summ_end_per_.push_back(summ_end_per_.back());
                }
            }
            tax_paid_.push_back(round(tax));
            output_time_.push_back(tmp);
            perc_earned = 0;
            tax = 0;
        } else if (i % deposit_rep_term_ == 0 && i != term_ && deposit_rep_ > 0) {
            perc_paid_.push_back(0);
            perc_acc_.push_back(0);
            tax_paid_.push_back(0);
            dep_rep_sum_.push_back(deposit_rep_);
            summ_end_per_.push_back(summ_end_per_.back() + deposit_rep_);
            output_time_.push_back(tmp);
        }
        
    }
}

double DebitModel::GetVectorSumm(const std::vector<double>& data) {
    double res = 0;
    for (auto v : data)
        res += v;
    return res;
}

double DebitModel::GetPercentSumm(){
    return kapitalization_ ? GetVectorSumm(perc_acc_) : GetVectorSumm(perc_paid_);
}

double DebitModel::GetResult() {
//    std::time_t start_time = std::mktime(&start_);
//    std::time_t fin_time = std::mktime(&(time_.back()));
//    const int seconds_per_day = 60*60*24;
//    int diff = std::difftime(fin_time, start_time) / seconds_per_day;
    
    return summ_ + GetPercentSumm() + GetDepositRepSumm() - GetTaxSumm();
    
}
