#include "credit_calc_view.h"
#include "ui_credit_calc_view.h"

CreditCalcView::CreditCalcView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditCalcView)
{
    ui->setupUi(this);
}

CreditCalcView::~CreditCalcView()
{
    delete ui;
}
