#ifndef DEBIT_CALC_VIEW_H
#define DEBIT_CALC_VIEW_H

#include <QWidget>
#include "../model/debit_model.h"
#include "QStandardItemModel"
#include <QChartView>
namespace Ui {
class DebitCalcView;
}

class DebitCalcView : public QWidget{
    Q_OBJECT

public:
    explicit DebitCalcView(QWidget *parent = nullptr);
    ~DebitCalcView();

private:
    Ui::DebitCalcView *ui;
    DebitModel* model;
    QStandardItemModel* table_model;
    QChartView* chartView;
    void FillTable(int kap_per, int deposit_rep_term, bool kapitalization, double deposit_rep);
    void MakeDonutChart(qreal summ, qreal dep_rep, qreal percents, qreal tax);
signals:
    void SignalSizeChanged();
private slots:
    void CBChanged();
    void CalcButtonClicked();
    void PaysGraphButtonClicked();


};

#endif // Debit_CALC_VIEW_H
