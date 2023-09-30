#include "credit_calc_view.h"
#include "ui_credit_calc_view.h"

CreditCalcView::CreditCalcView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditCalcView){
    ui->setupUi(this);
    model = new CreditModel;
    table_model = new QStandardItemModel;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(CalcBtnClicked()));
    this->setFixedSize(700, 850);
    ui->summ_le->setText("2500000");
    ui->term_le->setText("24");
    ui->perc_le->setText("8.25");
    ui->dateEdit->setDate({2023, 9, 15});
    QDoubleValidator* double_vall = new QDoubleValidator(0, 1000000000.0, 2, this);
    QIntValidator* int_vall = new QIntValidator(1, 200, this);
    QDoubleValidator* perc_vall = new QDoubleValidator(0.01, 100.0, 2, this);
    double_vall->setLocale(QLocale::English);
    int_vall->setLocale(QLocale::English);
    perc_vall->setLocale(QLocale::English);
    ui->summ_le->setValidator(double_vall);
    ui->term_le->setValidator(int_vall);
    ui->perc_le->setValidator(perc_vall);
}

CreditCalcView::~CreditCalcView()
{
    delete ui;
    delete model;
    delete table_model;
}

void CreditCalcView::CalcBtnClicked() {
    if (!ui->perc_le->text().isEmpty() && !ui->summ_le->text().isEmpty()
            && !ui->term_le->text().isEmpty() ) {
        double summ = ui->summ_le->text().toDouble();
        int term = ui->term_le->text().toInt();
        QDate date = ui->dateEdit->date();
        std::tm start {0, 0, 0, date.day(), date.month() - 1, date.year() - 1900};
        double rate = ui->perc_le->text().toDouble();
        bool type = true;
        if (ui->comboBox->currentIndex() == 1)
            type = false;
        model->SetData(summ, term, start, rate, type);
        double res = model->Calculate();
        if (type) {
            ui->m_pay_label->setText(QString::number(model->month_paid_[1],'f', 1));
        } else {
            ui->m_pay_label->setText(QString::number(model->month_paid_[1],'f', 1) +
                    "\u2192" + QString::number(model->month_paid_.back(),'f', 1));
        }
        ui->percent_label->setText(QString::number(model->GetPercSumm(),'f', 1));
        ui->res_paid_label->setText(QString::number(res,'f', 1));
        FillTable();
    }
}

void CreditCalcView::FillTable() {
    QStandardItem* item;
    QStringList horizontalHeader;
    horizontalHeader.append("Дата");
    horizontalHeader.append(" Сумма платежа");
    horizontalHeader.append(" Платеж по основному \n долгу");
    horizontalHeader.append(" Платеж по \n процентам");
    horizontalHeader.append(" Остаток \n долга");
    table_model->setHorizontalHeaderLabels(horizontalHeader);
    for (int i = 0; i < model->time_.size(); ++i) {
        QDate date(model->time_[i].tm_year + 1900, model->time_[i].tm_mon + 1, model->time_[i].tm_mday);
        item = new QStandardItem(date.toString());
        table_model->setItem(i, 0, item);
        if (i != 0) {
            item = new QStandardItem(QString::number(model->month_paid_[i],'f',0));
            table_model->setItem(i, 1, item);
            item = new QStandardItem(QString::number(model->main_debt_paid_[i],'f',0));
            table_model->setItem(i, 2, item);
            item = new QStandardItem(QString::number(model->per_paid_[i],'f',0));
            table_model->setItem(i, 3, item);
            item = new QStandardItem(QString::number(model->rem_debt_[i],'f',0));
            table_model->setItem(i, 4, item);
        }
        ui->tableView->setModel(table_model);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
}
