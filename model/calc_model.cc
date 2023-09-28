#include "calc_model.h"

namespace s21{
bool CalcModel::CheckParenthesis() {
    std::stack<char> par;
    for (auto c : input_str_) {
        if (c == '(')
            par.push('(');
        else if (c == ')') {
            if (!par.empty() && par.top() == '(')
                par.pop();
            else
                return false;
        }
    }
    return par.empty();
}
short CalcModel::Token::GetPriority(std::string oper) {
    short result = -1;
    if (kFunctions.find(oper) != kFunctions.end() || oper == "u-" || oper == "u+")
        result = 5;
    else if (oper == "^")
      result = 4;
    else if (oper == "*" || oper == "/" || oper == "mod")
      result = 3;
    else if (oper == "+" || oper == "-")
      result = 1;
    else if (oper == "(" || oper == ")")
      result = 0;
    else
        throw std::invalid_argument("unknown operation");
    return result;
}

std::vector<CalcModel::Token> CalcModel::Parse() {
    std::vector<Token> result;
    for (size_t i = 0; i < input_str_.size(); ++i) {
        if (input_str_[i] <= '9' && input_str_[i] >= '0') {
            std::pair<double, int> val_p = GetNumber(i);
            Token tok(val_p.first);
            result.push_back(tok);
            i += val_p.second - 1;
        } else if (input_str_[i] == 's' || input_str_[i] == 'c' || input_str_[i] == 't' || input_str_[i] == 'a' || input_str_[i] == 'l') {
            Token tok(GetFunc(i));
            result.push_back(tok);
            i += result.back().oper.size() - 1;
        } else if (IsOper(i)) {
            std::string oper;
            if (input_str_[i] == 'm') {
                oper = "mod";
                i += 2;
            } else if ((input_str_[i] == '-' || input_str_[i] == '+') && (result.empty() || result.back().oper == "(" )) {
                oper = input_str_[i] == '-' ? "u-" : "u+";
            } else {
                oper = input_str_[i];
            }
            Token tok(oper);
            result.push_back(tok);
        } else if (input_str_[i] == ' ') {
            continue;
        } else {
            throw std::invalid_argument("unknown operation");
        }
    }
    return result;
}

std::pair<double, int> CalcModel::GetNumber(size_t i) {
    std::string_view view = input_str_;
    double val = 0;
    int ind = 0;
    sscanf(view.substr(i).data(), "%lf%n", &val, &ind);
    return std::make_pair(val, ind);
}

std::string  CalcModel::GetFunc(size_t i) {
    std::string res;
    while (input_str_[i] >= 'a' && input_str_[i] <= 'z' && input_str_[i] != 'x')
        res.push_back(input_str_[i++]);
    return res;
}

bool CalcModel::IsOper(size_t i) {
    return input_str_[i] == '*' || input_str_[i] == '/' || input_str_[i] == '+' ||
    input_str_[i] == '-' || input_str_[i] == '^' || input_str_[i] == '(' || input_str_[i] == ')' || (input_str_[i] == 'm' && input_str_[i+1] == 'o' && input_str_[i+2] == 'd');
}

std::vector<CalcModel::Token> CalcModel::ShuntingYard(std::vector<Token> input) {
    std::stack<Token> oper;
std::vector<Token> result;
    for (auto t : input) {
        if (!t.is_oper) {
            result.push_back(t);
        } else {
            if (t.oper == "(")
                oper.push(t);
            else if (t.oper == ")") {
                while (oper.top().oper != "(") {
                    result.push_back(oper.top());
                    oper.pop();
                }
                oper.pop();
            } else {
                while (!oper.empty() && t.prior <= oper.top().prior ) {
                    result.push_back(oper.top());
                    oper.pop();
                }
                oper.push(t);
                }
                    
            }
        }
    while (!oper.empty()) {
        result.push_back(oper.top());
        oper.pop();
    }
    return result;
}

double CalcModel::Evaluate(std::string oper, double val1, double val2) {
    if (oper == "+")
        return val1 + val2;
    else if (oper == "-")
        return val2 - val1;
    else if (oper == "*")
        return val1 * val2;
    else if (oper == "/")
        return val2 / val1;
    else if (oper == "^")
        return pow(val2, val1);
    else if (oper == "mod")
        return fmod(val1, val2);
    else if (oper == "u-")
        return 0 - val1;
    else if (oper == "u+")
        return val1;
    else if (oper ==  "sin")
        return sin(val1);
    else if (oper ==  "cos")
        return cos(val1);
    else if (oper ==  "tan")
        return tan(val1);
    else if (oper ==  "acos")
        return acos(val1);
    else if (oper ==  "asin")
        return asin(val1);
    else if (oper ==  "atan")
        return atan(val1);
    else if (oper ==  "sqrt")
        return sqrt(val1);
    else if (oper ==  "ln")
        return log(val1);
    else
        return log10(val1);
}
double CalcModel::GetResult() {
    std::stack<double> temp;
    std::vector<Token> input = Parse();
    CheckInput(input);
    std::vector<Token> polish = ShuntingYard(input);
    for (auto t : polish) {
        if (!t.is_oper)
            temp.push(t.val);
        else {
            if (t.prior == 5) {
                if (temp.empty())
                    throw std::invalid_argument("invalid arg");
                double tmp_res = Evaluate(t.oper, temp.top(), 0);
                temp.pop();
                temp.push(tmp_res);
            } else {
                double val1, val2;
                
                val1 = temp.top();
                temp.pop();
                if (temp.empty())
                    throw std::invalid_argument("invalid arg");
                val2 = temp.top();
                temp.pop();
                temp.push(Evaluate(t.oper, val1, val2));
            }
        }
    }
//    if (temp.size() > 1)
//        throw std::invalid_argument("probably missing operator");
    return temp.top();
}

void CalcModel::ReplaceX(std::string x) {
    x = "(" + x + ")";
    size_t ind = 0;
    while ((ind = input_str_.find("x")) != std::string::npos) {
        input_str_.replace(ind, 1, x);
    }

}

void CalcModel::CheckInput(std::vector<Token> input) {
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i].is_oper) {
            if (i + 1 == input.size() && input[i].oper != ")")
                throw std::invalid_argument("probably missing operand");
        } else {
            if (i + 1 < input.size() && kFunctions.find(input[i + 1].oper) != kFunctions.end() )
                throw std::invalid_argument("probably missing operation");
        }
    }
}

//std::pair<std::vector<double>, std::vector<double>> CalcModel::GetDataForGraph(std::string func, double xmin, double xmax) {
//    std::pair<std::vector<double>, std::vector<double>> res;
    
//    double points = 1000, step = 0;
//    if (xmax > xmin)
//        step = (xmax - xmin)/points;
//    double x = xmin;
//    while (x <= xmax) {
//        SetInputStr(func);
//        res.first.push_back(x);
//        ReplaceX(std::to_string(x));
//        res.second.push_back(GetResult());
//        x += step;
//    }
//    return res;
//}
}
