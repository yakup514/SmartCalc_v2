#include "../credit_model.h"
#define ACC1 1e-1
TEST(cr, test1) {
    std::tm t;
    t.tm_mday = 29;
    t.tm_mon = 8;
    t.tm_year = 123;
    CreditModel m;
    m.SetData(250000.0, 24, t, 8.25, 1);
    double res = m.Calculate();
    EXPECT_NEAR (res,  272025.82, ACC1);
}

TEST(cr, test2) {
    std::tm t;
    t.tm_mday = 29;
    t.tm_mon = 8;
    t.tm_year = 123;
    CreditModel m;
    m.SetData(250000.0, 24, t, 8.25, 0);
    double res = m.Calculate();
    m.ClearData();
    EXPECT_NEAR (res,  271464.52, ACC1);
}

