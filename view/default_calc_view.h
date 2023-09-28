#ifndef DEFAULTCALCVIEW_H
#define DEFAULTCALCVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include "../controller/default_calc_controller.h"
#include "graph_window.h"
class DefaultCalcView :public QWidget
{
     Q_OBJECT
public:
    DefaultCalcView(QWidget *parent = nullptr);
    QLineEdit *line1_;
    QLineEdit *line2_;
    QPushButton* CreateButton(const QString& str);
    QString data_, xval_;
    bool x_mode_ = false;
    DefaultCalcController* controller;
public slots:
    void SlotDigitOrOperationButtonClicked();
    void SlotCalculateButtonClicked();
    void SlotGraphButtonClicked();
};

#endif // DEFAULTCALCVIEW_H
