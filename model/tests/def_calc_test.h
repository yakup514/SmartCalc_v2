#include "../calc_model.h"
#define ACC 1e-7
TEST(par, test1) {
    s21::CalcModel model("()");
    EXPECT_EQ (true, model.CheckParenthesis());
}

TEST(par, test2) {
    s21::CalcModel model("(1+(2-3)*(-3)+2)");
    EXPECT_EQ (true, model.CheckParenthesis());
}

TEST(par, test3) {
    try {
        s21::CalcModel model("(())())");
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "incorrect bracket sequence");
    }
}

TEST(par, test4) {
    try {
    s21::CalcModel model("(()(())");
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "incorrect bracket sequence");
    }
}

TEST(calc, test1) {
    s21::CalcModel model("(4^acos(2/4))");
    EXPECT_NEAR (model.GetResult(), 4.27047072069, ACC);
}

TEST(calc, test2) {
    s21::CalcModel model("(4^acos(2/4)/tan(2*2)/5^acos(2/4)/tan(tan(tan(2*2))))");
    EXPECT_NEAR (model.GetResult(), -0.58934796, ACC);
}

TEST(calc, test3) {
    s21::CalcModel model("acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)");
    EXPECT_NEAR (model.GetResult(), 1.59353092682, ACC);
}

TEST(calc, test4) {
    s21::CalcModel model("(1+3-2)*(+2)*cos(3)");
    EXPECT_NEAR (model.GetResult(), -3.95996998, ACC);
}

TEST(calc, test5) {
    s21::CalcModel model("ln((1+3-2)*(+2))*cos(3)^2");
    EXPECT_NEAR (model.GetResult(), 1.3586865, ACC);
}

TEST(calc, test6) {
    s21::CalcModel model("asin(1) + sqrt(4)*ln(0.1)");
    EXPECT_NEAR (model.GetResult(),  -3.034373859, ACC);
}

TEST(calc, test7) {
    s21::CalcModel model("5 mod 2 + log(10) + 4^(-1)");
    EXPECT_NEAR (model.GetResult(),  3.25, ACC);
}

TEST(calc, test8) {
    s21::CalcModel model("5 + x");
    model.ReplaceX("2");
    EXPECT_NEAR (model.GetResult(),  7.0, ACC);
}

TEST(err, test1) {
    try {
        s21::CalcModel model("5 mod 2 + log() + 4^(-1)");
        model.GetResult();
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "invalid arg");
    }
}

TEST(err, test2) {
    try {
        s21::CalcModel model("5 mod 2 +- log(2) + 4^(-1)");
        model.GetResult();
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "invalid arg");
    }
}

TEST(err, test3) {
    try {
        s21::CalcModel model("5 mod 2 +q- log(2) + 4^(-1)");
        model.GetResult();
        FAIL();
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "unknown operation");
    }
}

TEST(err, test4) {
    try {
        s21::CalcModel model("5 mod 2 +a- log(2) + 4^(-1)");
        model.GetResult();
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "unknown operation");
    }
}

TEST(err, test5) {
    try {
        s21::CalcModel model("");
        model.SetInputStr("cos");
        model.GetResult();
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "probably missing operand");
    }
}

TEST(err, test6) {
    try {
        s21::CalcModel model("");
        model.SetInputStr("(-)");
        model.GetResult();
    } catch (const std::invalid_argument& ex) {
        EXPECT_STREQ(ex.what(), "invalid arg");
    }
}


