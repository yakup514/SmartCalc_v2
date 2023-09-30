#include "debit_calc_view.h"
#include "QtCore/qobjectdefs.h"
#include "ui_debit_calc_view.h"
#include "QStandardItem"
#include <QValidator>
#include <QPieSeries>

DebitCalcView::DebitCalcView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebitCalcView) {
    ui->setupUi(this);
    model = new DebitModel;
    table_model = new QStandardItemModel;
    ui->sum_le->setText("700000");
    ui->period_le->setText("12");
    ui->dateEdit->setDate({2023, 9, 15});
    ui->percent_le->setText("8");
    ui->percent_label->setText("Периодичность капитализации:");
    ui->curr_qb->addItem("\u20BD");
    ui->curr_qb->addItem("\u20AC");
    ui->curr_qb->addItem("\u0024");
    ui->curr_qb->addItem("\u5143");
    ui->curr_qb->setCurrentIndex(0);
    connect(ui->capitalization_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(CBChanged()));
    connect(ui->calc_pb, SIGNAL(clicked()), this, SLOT(CalcButtonClicked()));
    connect(ui->pays_graph_btn, SIGNAL(clicked()), this, SLOT(PaysGraphButtonClicked()));
    this->setFixedSize(700, 490);
    ui->pays_graph_btn->setVisible(false);
    ui->tableView->setVisible(false);
    QDoubleValidator* double_vall = new QDoubleValidator(0, 1000000000.0, 2, this);
    QIntValidator* int_vall = new QIntValidator(1, 100, this);
    QDoubleValidator* perc_vall = new QDoubleValidator(0.01, 999.0, 2, this);
    double_vall->setLocale(QLocale::English);
    int_vall->setLocale(QLocale::English);
    perc_vall->setLocale(QLocale::English);
    ui->sum_le->setValidator(double_vall);
    ui->percent_le->setValidator(perc_vall);
    ui->rep_sum_le->setValidator(double_vall);
    ui->period_le->setValidator(int_vall);
}

DebitCalcView::~DebitCalcView() {
    delete model;
    delete table_model;
    delete ui;
}

void DebitCalcView::CBChanged() {
    if (ui->capitalization_cb->currentIndex() == 0)
        ui->percent_label->setText("Периодичность капитализации:");
    else
        ui->percent_label->setText("Периодичность выплат:");
}

void DebitCalcView::CalcButtonClicked() {
    if (!ui->percent_le->text().isEmpty() && !ui->sum_le->text().isEmpty()
            && !ui->period_le->text().isEmpty() && !ui->rep_sum_le->text().isEmpty()) {
    bool curr_is_rub = true;
    if (ui->curr_qb->currentIndex() == 1)
        curr_is_rub = false;
    double sum = ui->sum_le->text().toDouble();
    int term = ui->period_le->text().toInt();
    QDate date = ui->dateEdit->date();
    std::tm start {0, 0, 0, date.day(), date.month() - 1, date.year() - 1900};
    double rate = ui->percent_le->text().toDouble();
    int kap_per = 1;
    if (ui->percent_perio_cb->currentIndex() == 0)
        kap_per = term;
    else if (ui->percent_perio_cb->currentIndex() == 1)
        kap_per = 1;
    else if (ui->percent_perio_cb->currentIndex() == 2)
        kap_per = 6;
    else if (ui->percent_perio_cb->currentIndex() == 3)
        kap_per = 12;
    bool kapitalization = true;
    if (ui->capitalization_cb->currentIndex() == 1)
        kapitalization = false;
    double deposit_rep = ui->rep_sum_le->text().toDouble();
    int deposit_rep_term = 1;
    if (ui->rep_cb->currentIndex() == 0)
        deposit_rep = 0.0;
    else if (ui->rep_cb->currentIndex() == 1)
        deposit_rep_term = 1;
    else if (ui->rep_cb->currentIndex() == 2)
        deposit_rep_term = 6;
    else if (ui->rep_cb->currentIndex() == 3)
        deposit_rep_term = 12;
    model->SetData(sum, term,start, rate, kap_per, kapitalization, curr_is_rub, deposit_rep, deposit_rep_term);
    ui->sum_label->setText(ui->sum_le->text());
    model->Calculate();
    ui->profit_label->setText(QString::number(model->GetResult(),'f',0));
    ui->rep_sum_label->setText(QString::number(model->GetDepositRepSumm(),'f',0));
    ui->percent_acc_label->setText(QString::number(model->GetPercentSumm(),'f',0));
    ui->tax_paid_label->setText(QString::number(model->GetTaxSumm()));
    ui->pays_graph_btn->setVisible(true);
    FillTable(kap_per, deposit_rep_term, kapitalization, deposit_rep);
    MakeDonutChart((qreal)sum, (qreal)model->GetDepositRepSumm(), (qreal)model->GetPercentSumm(), (qreal)model->GetTaxSumm());
    }
}

void DebitCalcView::PaysGraphButtonClicked() {
    if(ui->pays_graph_btn->text() == "График выплат") {
        ui->pays_graph_btn->setText("Скрыть");
        ui->tableView->setVisible(true);
        this->setFixedSize(700, 850);
        emit SignalSizeChanged();
    } else {
        ui->pays_graph_btn->setText("График выплат");
        ui->tableView->setVisible(false);
        this->setFixedSize(700, 490);
        emit SignalSizeChanged();
    }

}

void DebitCalcView::FillTable(int kap_per, int deposit_rep_term,  bool kapitalization, double deposit_rep) {
    table_model->clear();
    QStandardItem* item;
    QStringList horizontalHeader;
    horizontalHeader.append("Дата \nрасчета");
    horizontalHeader.append(" Начислено \n процентов, \n" + ui->curr_qb->currentText());
    horizontalHeader.append(" Уплаченный \n налог, \n" + ui->curr_qb->currentText());
    if (kapitalization)
        horizontalHeader.append(" Добавлено \n ко вкладу, \n" + ui->curr_qb->currentText());
    else
        horizontalHeader.append(" Выплачено \n процентов, \n" + ui->curr_qb->currentText());
    horizontalHeader.append(" Пополнение \n вклада, \n" + ui->curr_qb->currentText());
    horizontalHeader.append(" Сумма вклада \n на конец срока, \n" + ui->curr_qb->currentText());
    table_model->setHorizontalHeaderLabels(horizontalHeader);
    for (int i = 1; i < model->output_time_.size(); ++i) {
            QDate date(model->output_time_[i].tm_year + 1900, model->output_time_[i].tm_mon + 1, model->output_time_[i].tm_mday);
            item = new QStandardItem(date.toString());
            table_model->setItem(i - 1, 0, item);
            if (kapitalization) {
                item = new QStandardItem(QString::number(model->perc_acc_[i],'f',0));
                table_model->setItem(i - 1, 1, item);
            } else {
                item = new QStandardItem(QString::number(model->perc_paid_[i],'f',0));
                table_model->setItem(i - 1, 1, item);
            }
            item = new QStandardItem(QString::number(model->tax_paid_[i],'f',0));
            table_model->setItem(i - 1, 2, item);
            if (kapitalization) {
                item = new QStandardItem(QString::number(model->perc_acc_[i] - model->tax_paid_[i],'f',0));
                table_model->setItem(i - 1, 3, item);
            } else {
                item = new QStandardItem(QString::number(model->perc_paid_[i] - model->tax_paid_[i],'f',0));
                table_model->setItem(i - 1, 3, item);
            }
            item = new QStandardItem(QString::number(model->dep_rep_sum_[i],'f',0));
            table_model->setItem(i - 1, 4, item);
            item = new QStandardItem(QString::number(model->summ_end_per_[i],'f',0));
            table_model->setItem(i - 1, 5, item);
    }
    ui->tableView->setModel(table_model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void DebitCalcView::MakeDonutChart(qreal summ, qreal dep_rep, qreal percents, qreal tax) {
    if (!ui->donut_layout->isEmpty()){
        delete chartView;
    }

    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart *chart = chartView->chart();
    chart->legend()->setVisible(false);
    auto donut = new QPieSeries(this);
    auto slice_summ = new QPieSlice("", summ);
    slice_summ->setColor(QColorConstants::Svg::orange);
    donut->append(slice_summ);
    auto slice_rep = new QPieSlice("", dep_rep);
    slice_rep->setColor(QColorConstants::Svg::green);
    donut->append(slice_rep);
    auto slice_per = new QPieSlice("", percents);
    slice_per->setColor(QColorConstants::Svg::cyan);
    donut->append(slice_per);
    auto slice_tax = new QPieSlice("", tax);
    slice_tax->setColor(QColorConstants::Svg::red);
    donut->append(slice_tax);
    donut->setHoleSize(0.5);
    chartView->chart()->addSeries(donut);
    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setBackgroundVisible(false);

    ui->donut_layout->setSpacing(0);
    ui->donut_layout->setContentsMargins(0, 0, 0, 0);

  ui->donut_layout->addWidget(chartView, 0, 1);


  chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
