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



