#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include "../model/calc_model.h"
#include <string>
#include <QVector>
class GraphController
{
public:
    GraphController() {model = new s21::CalcModel("");}
    void SetData(std::string func, double xmin, double xmax);
    std::pair<QVector<double>, QVector<double>> GetData(std::string func, double xmin, double xmax, double ymin, double ymax);
    ~GraphController() {delete model;};
private:
    s21::CalcModel* model;
};

#endif // GRAPHCONTROLLER_H
