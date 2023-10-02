#ifndef calc_model_h
#define calc_model_h

#include <string>
#include <string_view>
#include <vector>
#include <stack>
#include <unordered_set>
#include <cmath>
#include <iostream>
static const std::unordered_set<std::string> kFunctions = {"sin",  "cos",  "tan", "acos", "asin", "atan", "sqrt", "ln",  "log"};
namespace s21 {

class CalcModel {
public:
    CalcModel(std::string input) : input_str_{input} {
        if (!CheckParenthesis())
            throw std::invalid_argument("incorrect bracket sequence");
    };
    void SetInputStr(std::string str) {
        input_str_ = str;
    }
    void ReplaceX(std::string x);
    bool CheckParenthesis();
    double GetResult();
    std::pair<std::vector<double>, std::vector<double>> GetDataForGraph(std::string func, double xmin, double xmax);
   
private:
   
    std::string input_str_;
    struct Token {
        Token(double val) : is_oper{false}, val{val} {};
        Token(std::string oper) :is_oper{true}, prior{GetPriority(oper)}, oper{oper} {};
        short GetPriority(std::string oper);
        bool is_oper;
        short prior;
        double val;
        std::string oper;
    };
    std::vector<Token> Parse();
    std::pair<double, int> GetNumber(size_t i);
    std::string GetFunc(size_t i);
    bool IsOper(size_t i);
    std::vector<Token> ShuntingYard(std::vector<Token> input);
    double Evaluate(std::string oper, double op1, double op2);

    void CheckInput(std::vector<Token> input);
    
    
//public:
//    void PrintVec()  {
//        std::vector<Token> data = Parse();
//        for (auto t : data) {
//            if (!t.is_oper)
//                std::cout << t.val << '\n';
//            else
//                std::cout << t.oper << " prior = " << t.prior << '\n';
//
//        }
//    }
//    void PrintStack()  {
//        std::vector<Token> data1 = Parse();
//        std::vector<Token> data = ShuntingYard(data1);
//        std::cout<< "\n";
//        for (auto t : data) {
//            t.is_oper ? std::cout << t.oper << ' ' : std::cout << t.val << ' ';
//        }
//    }
//    
};
}
#endif
