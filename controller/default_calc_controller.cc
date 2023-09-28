#include "default_calc_controller.h"

DefaultCalcController::DefaultCalcController() {
    model = new s21::CalcModel("");
}

DefaultCalcController::DefaultCalcController(std::string str) {
    model = new s21::CalcModel(str);
}

DefaultCalcController::DefaultCalcController(std::string str, std::string x) {
     model = new s21::CalcModel(str);
     model->ReplaceX(x);
}

void DefaultCalcController::SetData(std::string str, std::string x ) {
    model->SetInputStr(str);
    model->ReplaceX(x);
}

double DefaultCalcController::Calculate() {
    return model->GetResult();
}


