#include "credit_model.h"

CreditModel::CreditModel() {

}

void CreditModel::SetData(double summ, int term, std::tm start, double rate, bool type) noexcept {
    summ_ = summ;
    term_ = term;
    start_ = start;
    rate_ = rate;
    type_anyit_ = type;
}

void CreditModel::ClearData() noexcept {
    rem_debt_.clear();
    per_paid_.clear();
    month_paid_.clear();
    main_debt_paid_.clear();
    time_.clear();
}

double CreditModel::Calculate() {
    rem_debt_.push_back(summ_);
    per_paid_.push_back(0.0);
    month_paid_.push_back(0.0);
    main_debt_paid_.push_back(0.0);
    time_.push_back(start_);
    double res = 0;
    for (int i = 1; i < term_ + 1; ++i) {
        std::tm tmp = start_;
        tmp.tm_mon = (start_.tm_mon + i) % 12;
        tmp.tm_year = (start_.tm_mon + i) / 12 + start_.tm_year;
        tmp.tm_mday = start_.tm_mday > GetDaysInMonthQua(tmp) ? GetDaysInMonthQua(tmp) : start_.tm_mday;
        std::tm last_m_d = time_.back();
        last_m_d.tm_mday = GetDaysInMonthQua(last_m_d);
        std::tm first_m_d = tmp;
        first_m_d.tm_mday = 1;
        double p_pay = rem_debt_.back() *rate_ * ((GetTimeDiff(time_.back(), last_m_d)+ 0) / (double)GetDaysInYearQua(time_.back()) + (GetTimeDiff(first_m_d, tmp) + 1) / (double)GetDaysInYearQua(tmp)) / 100.0;
        if (type_anyit_) {
            double m_pay = summ_ *(rate_/(100 *12.0))* pow((1.0 + rate_/(100 *12.0)), (double)term_)/ (pow((1.0 + rate_/(100 *12.0)), (double)term_) - 1.0);
           // res += std::round(m_pay);
           
            p_pay > m_pay ? p_pay = m_pay : 1;
            per_paid_.push_back(p_pay);
            if (i == term_) {
                month_paid_.push_back(rem_debt_.back() + p_pay);
                main_debt_paid_.push_back(rem_debt_.back());
                rem_debt_.push_back( rem_debt_.back() - (month_paid_.back() - p_pay));
            } else {
                month_paid_.push_back(m_pay);
                main_debt_paid_.push_back(m_pay - p_pay);
                rem_debt_.push_back( (rem_debt_.back() - (m_pay - p_pay)));
            }
        } else {
            per_paid_.push_back(p_pay);
            month_paid_.push_back(p_pay + summ_/term_);
            main_debt_paid_.push_back(summ_/term_);
            rem_debt_.push_back(rem_debt_.back() - summ_/term_);
        }
        time_.push_back(tmp);
    }
    for (auto v : month_paid_)
        res += v;
    return res;
}

