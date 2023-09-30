#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    def_calc = new DefaultCalcView(this);
    deb_calc = new DebitCalcView(this);
    cred_calc = new CreditCalcView(this);
    deb_calc->hide();
    cred_calc->hide();
    mbar_ = new QMenuBar;
    QMenu* fileMenu = new QMenu("options");
    fileMenu->addAction("default", this, SLOT(SlotDefCalc()));
    fileMenu->addAction("credit", this, SLOT(SlotCreditCalc()));
    fileMenu->addAction("debit", this, SLOT(SlotDebitCalc()));
    connect(deb_calc, SIGNAL(SignalSizeChanged()), this, SLOT(SlotDebitCalcSizeChanged()));
    mbar_->addMenu(fileMenu);
    this->setMenuBar(mbar_);
   // def_calc->show();
    this->setFixedSize(def_calc->size());
  //  qDebug()<< def_calc->size();
}

MainWindow::~MainWindow() {

}

void MainWindow::SlotDefCalc(){
    def_calc->show();
    deb_calc->hide();
    cred_calc->hide();
    this->setFixedSize(def_calc->size());
//
}

void MainWindow::SlotCreditCalc() {
    def_calc->hide();
    deb_calc->hide();
    cred_calc->show();
    this->setFixedSize(cred_calc->size());
}

void MainWindow::SlotDebitCalc(){
    def_calc->hide();
    deb_calc->show();
    cred_calc->hide();
    this->setFixedSize(deb_calc->size());
    //    setSizePolicy(QSizePolicy::Expanding	, QSizePolicy::Expanding	);
}

void MainWindow::SlotDebitCalcSizeChanged(){
    this->setFixedSize(deb_calc->size());
}

