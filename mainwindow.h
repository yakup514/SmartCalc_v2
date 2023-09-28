#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include "view/default_calc_view.h"
#include "view/debit_calc_view.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DefaultCalcView* def_calc;
    DebitCalcView* deb_calc;

    QMenuBar* mbar_;
public slots:
    void SlotDefCalc();
    void SlotCreditCalc();
    void SlotDebitCalc();
    void SlotDebitCalcSizeChanged();
};
#endif // MAINWINDOW_H
