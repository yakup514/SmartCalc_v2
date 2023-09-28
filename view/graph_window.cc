#include "graph_window.h"
#include "ui_graph_window.h"
#include <QValidator>
GraphWindow::GraphWindow(QWidget *parent, QString data) :
    QDialog(parent),
    ui(new Ui::GraphWindow), func_(data){
    ui->setupUi(this);
    QIntValidator* int_val = new QIntValidator(-1000000, 1000000, this);
    //int_vall->setLocale(QLocale::English);
    ui->max_x_le->setValidator(int_val);
    ui->max_y_le->setValidator(int_val);
    ui->min_x_le->setValidator(int_val);
    ui->min_y_le->setValidator(int_val);
    controller_ = new GraphController();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(SlotRepolotButtonClicked()) );
    ui->plot_func_le->setText(func_);
    PlotFunc();

}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::PlotFunc() {
    QString func = ui->plot_func_le->text();

    double xmax, xmin, ymax, ymin;
    xmax =  ui->max_x_le->text().toDouble();
    ymax =  ui->max_y_le->text().toDouble();
    xmin =  ui->min_x_le->text().toDouble();
    ymin =  ui->min_y_le->text().toDouble();
    if (xmax > xmin && ymax > ymin && !func.isEmpty()) {
        std::pair<QVector<double>, QVector<double>> plot_data;
        try {
        plot_data = controller_->GetData(func.toStdString(), xmin, xmax, ymin, ymax);
        ui->widget->xAxis->setRange(xmin, xmax);
        ui->widget->yAxis->setRange(ymin, ymax);
        ui->widget->clearGraphs();
        ui->widget->addGraph();
        ui->widget->graph(0)->addData(plot_data.first, plot_data.second);
        ui->widget->replot();
        } catch(const std::invalid_argument& ex) {
            ui->plot_func_le->setText(ex.what());
        }
    }

}

void GraphWindow::SlotRepolotButtonClicked() {
    PlotFunc();
}
