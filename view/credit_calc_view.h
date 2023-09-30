#ifndef CREDIT_CALC_VIEW_H
#define CREDIT_CALC_VIEW_H

#include <QWidget>

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
};

#endif // CREDIT_CALC_VIEW_H
