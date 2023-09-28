#include "../debit_model.h"
#define ACC1 1e-1
TEST(deb, test1) {
    std::tm t;
    t.tm_mday = 27;
    t.tm_mon = 8;
    t.tm_year = 123;
    DebitModel model(700000.0, 12, t, 8.0, 6, 1, 1, 10000.0, 6);
    model.Calculate();
    std::vector<int> test_v{700000, 737887, 767564};
    for (size_t i = 0; i < model.summ_end_per_.size(); ++i )
        EXPECT_EQ (std::round(model.summ_end_per_[i]),  test_v[i]);
}

TEST(deb, test2) {
    std::tm t;
    t.tm_mday = 27;
    t.tm_mon = 8;
    t.tm_year = 123;
    DebitModel model;
    model.SetData(700000.0, 12, t, 8.0, 12, 0, 1, 10000.0, 6);
    model.Calculate();
    std::vector<int> test_s{700000, 710000, 710000};
    std::vector<int> test_p{ 0, 0, 56442};
    for (size_t i = 0; i < model.summ_end_per_.size(); ++i )
        EXPECT_EQ (std::round(model.summ_end_per_[i]),  test_s[i]);
    for (size_t i = 1; i < model.perc_paid_.size(); ++i )
        EXPECT_EQ (std::round(model.perc_paid_[i]),  test_p[i]);
    EXPECT_EQ(std::round(model.GetPercentSumm()), 56442);
    EXPECT_EQ(std::round(model.GetResult()), 766442);
    model.DataClear();
}

TEST(deb, test3) {
    std::tm t;
    t.tm_mday = 27;
    t.tm_mon = 8;
    t.tm_year = 123;
    DebitModel model;
    model.SetData(700000.0, 12, t, 10.0, 12, 0, 0, 10000.0, 6);
    model.Calculate();
    EXPECT_EQ(std::round(model.GetResult()), 778084);
    model.DataClear();
}

TEST(deb, test4) {
    std::tm t;
    t.tm_mday = 27;
    t.tm_mon = 8;
    t.tm_year = 123;
    DebitModel model;
    model.SetData(700000.0, 12, t, 22.0, 12, 0, 1, 10000.0, 6);
    model.Calculate();
    EXPECT_EQ(std::round(model.GetResult()), 855340);
    model.DataClear();
}

TEST(deb, test5) {
    std::tm t;
    t.tm_mday = 27;
    t.tm_mon = 8;
    t.tm_year = 123;
    DebitModel model;
    model.SetData(700000.0, 12, t, 22.0, 6, 0, 1, 10000.0, 1);
    model.Calculate();
    EXPECT_EQ(std::round(model.GetResult()), 965663);
    model.DataClear();
}

