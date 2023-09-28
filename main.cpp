#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile style_file(":/style.qss");

      if (style_file.open(QFile::ReadOnly)) {
        QString style(style_file.readAll());
        a.setStyleSheet(style);
        style_file.close();
      } else {
        qDebug() << "not opened style";
      }
    MainWindow w;
    w.show();
    return a.exec();
}
