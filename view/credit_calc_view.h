#ifndef CREDIT_CALC_VIEW_H
#define CREDIT_CALC_VIEW_H

#include <QWidget>
#include "../model/credit_model.h"
#include "QStandardItemModel"
namespace Ui {
class CreditCalcView;
}

class CreditCalcView : public QWidget
{
    Q_OBJECT

public:
    explicit CreditCalcView(QWidget *parent = nullptr);
    ~CreditCalcView();

private:
    Ui::CreditCalcView *ui;
    CreditModel* model;
    QStandardItemModel* table_model;
private slots:
    void CalcBtnClicked();
    void FillTable();
};

#endif // CREDIT_CALC_VIEW_H
