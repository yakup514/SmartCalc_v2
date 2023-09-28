#include "default_calc_view.h"

DefaultCalcView::DefaultCalcView(QWidget *parent)
: QWidget(parent){
    this->setFixedSize(420,420);
    controller = new DefaultCalcController();
    line1_ = new QLineEdit;
    line1_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    line2_ = new QLineEdit;
    line2_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    line2_->setText("0");
    line1_->setAlignment(Qt::AlignRight);
    line1_->setReadOnly(true);
    line1_->setObjectName("line1_");
    line2_->setObjectName("line2_");
    line2_->setReadOnly(true);
    line2_->setAlignment(Qt::AlignRight);
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(line1_, 0, 0, 1, 7);
    layout->addWidget(line2_, 1, 0, 1, 7);
    QString buttons[5][7] = {{"(", ")", "^", "AC", "±", "del", "/"},
                               {"cos", "acos", "sqrt", "7", "8", "9", "*"},
                               {"sin", "asin", "ln", "4", "5", "6", "-"},
                               {"tan", "atan", "log", "1", "2", "3", "+"},
                               {"graph", "mod", "x", "0", "e", ".", "="}};
    for (int i = 0; i < 5; ++i) {
       for (int j = 0; j < 7; ++j) {
         if (buttons[i][j] != "0" &&
             !buttons[i][j].isEmpty()) {
           layout->addWidget(CreateButton(buttons[i][j]), i + 2, j);
         }
       }
     }
    layout->addWidget(CreateButton("0"), 6, 3, 1, 1);
    setLayout(layout);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
}

QPushButton *DefaultCalcView::CreateButton(const QString &str) {
    QPushButton* button = new QPushButton(str);
      if (str == "+" || str == "-" || str == "*" || str == "/" || str == "=") {
        button->setObjectName("orange_button");
      } else if (str == "0" || str == "1" || str == "2" || str == "3" ||
                 str == "4" || str == "5" || str == "6" || str == "7" ||
                 str == "8" || str == "9" || str == "." || str == "e") {
        button->setObjectName("numeric_button");
      }
      button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      if (str != "graph" && str != "=")
        connect(button, SIGNAL(clicked()), this, SLOT(SlotDigitOrOperationButtonClicked()));
      else if (str == "=")
        connect(button, SIGNAL(clicked()), this, SLOT(SlotCalculateButtonClicked()));
      else if (str == "graph")
        connect(button, SIGNAL(clicked()), this, SLOT(SlotGraphButtonClicked()));
      return button;
}

void DefaultCalcView::SlotDigitOrOperationButtonClicked(){
    QString str = ((QPushButton*)sender())->text();
   // QString tmp;
    if (str == "AC") {
        data_.clear();
        xval_.clear();
        line2_->setText("0");
    } else if (str == ".") {
        if (!x_mode_)
            data_.isEmpty() ? data_ = "0." : data_ += ".";
        else
            xval_.isEmpty() ? xval_ = "0." : xval_ += ".";
    } else if (str == "del") {
        if (!x_mode_ && !data_.isEmpty())
            data_.chop(1);
        else if (x_mode_ && !xval_.isEmpty())
            xval_.chop(1);
    } else if(str == "±") {
        if (!x_mode_) {
            if (data_.isEmpty())
                data_ += "-";
            else if (data_[0] == '+')
                data_[0] = '-';
            else if (data_[0] == '-' )
                data_[0] = '+';
            else
                data_ = "-" + data_;
        } else {
            if (xval_.isEmpty())
                xval_ += "-";
            else if (xval_[0] == '+')
                xval_[0] = '-';
            else if (xval_[0] == '-' )
                xval_[0] = '+';
            else
                xval_ = "-" + xval_;
        }
    } else if (str != "del") {
        if (!x_mode_)
            data_ += str;
        else
            xval_ += str;
    }
    if (!x_mode_)
        line1_->setText(data_);
    else
        line1_->setText("x = " + xval_);
}

void DefaultCalcView::SlotCalculateButtonClicked() {
    if (!data_.contains('x') && !data_.isEmpty()) {
        controller->SetData(data_.toStdString());
        QString res_str;
        try {
            double res = controller->Calculate();
            res_str = QString::number(res);
            line2_->setText(res_str);
            data_ = res_str;
        } catch (const std::invalid_argument& ex) {
            line2_->setText(QString::fromStdString(ex.what()));
        }

    } else if (!x_mode_ && !data_.isEmpty()) {
        line2_->setText("INPUT X PLEASE AND PRESS =");
        x_mode_ = true;
        xval_.clear();
    } else if (!data_.isEmpty()){
        x_mode_ = false;
        controller->SetData(data_.toStdString(), xval_.toStdString());
        QString res_str;
        try {
            double res = controller->Calculate();
            res_str = QString::number(res);
            line1_->setText(data_ + ", x = " + xval_);
            line2_->setText(res_str);
            data_ = res_str;
        } catch (const std::invalid_argument& ex) {
             line2_->setText(QString::fromStdString(ex.what()));
             line1_->setText(data_ + ", x = " + xval_);
             data_.clear();
        }
    }

}

void DefaultCalcView::SlotGraphButtonClicked() {
    if (!data_.isEmpty()) {
    GraphWindow* gw = new GraphWindow(this, data_);
    gw->setModal(true);
    gw->setWindowTitle("Graph");
    gw->show();

    }
}
