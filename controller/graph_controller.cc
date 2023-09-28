#include "graph_controller.h"




void GraphController::SetData(std::string func, double xmin, double xmax){

}

std::pair<QVector<double>, QVector<double>> GraphController::GetData(std::string func, double xmin, double xmax, double ymin, double ymax){
    std::pair<QVector<double>, QVector<double>> res;

        double points = 10000, step = 0;
        if (xmax > xmin)
            step = (xmax - xmin)/points;
        double x = xmin;
        while (x <= xmax) {
            model->SetInputStr(func);
            res.first.push_back(x);
            model->ReplaceX(std::to_string(x));
            double tmp = model->GetResult();
            if (tmp >= ymax) {
                res.second.push_back(ymax);
                res.first.push_back(x + step/10);
                res.second.push_back(NAN);
                while (tmp >= ymax && x <= xmax) {
                    x += step;
                    model->SetInputStr(func);
                    model->ReplaceX(std::to_string(x));
                    tmp = model->GetResult();
                }
            } else if (tmp <= ymin ) {
                res.second.push_back(ymin);
                res.first.push_back(x + step/10);
                res.second.push_back(NAN);
                while (tmp <= ymin && x <= xmax) {
                    x += step;
                     model->SetInputStr(func);
                    model->ReplaceX(std::to_string(x));
                    tmp = model->GetResult();
                }
            } else {
                res.second.push_back(tmp);
                x += step;
            }

        }
        return res;
}
