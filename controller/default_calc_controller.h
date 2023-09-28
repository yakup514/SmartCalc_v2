#ifndef DEFAULTCALCCONTROLLER_H
#define DEFAULTCALCCONTROLLER_H
#include "../model/calc_model.h"
#include <string>
class DefaultCalcController {
public:
    DefaultCalcController();
    ~DefaultCalcController(){delete model;};
    DefaultCalcController(std::string str);
    DefaultCalcController(std::string str, std::string x);
   // void SetData(std::string);
    void SetData(std::string str, std::string x = " ");
    double Calculate();
private:
    s21::CalcModel* model;

};

#endif // DEFAULTCALCCONTROLLER_H
