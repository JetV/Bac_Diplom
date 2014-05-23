#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLibrary>
#include <QThread>
#include "ctworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_returnPressed();
    void ready();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    _dll_func getFun;
    double result_;
    CTWorker* worker_;
    QThread* thread_;
    UsrParm strucArg_;
    void runThread(double arg, _dll_func func);
};

#endif // MAINWINDOW_H
