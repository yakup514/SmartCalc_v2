#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <QDialog>
#include "../controller/graph_controller.h"
namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr, QString data  = "");
    ~GraphWindow();

private:
    Ui::GraphWindow *ui;
    GraphController* controller_;
    QString func_;
    void PlotFunc();
private slots:
    void SlotRepolotButtonClicked();
};

#endif // GRAPH_WINDOW_H
