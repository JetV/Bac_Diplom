#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLibrary>
#include <QThread>
#include <QDebug>
#include "ctworker.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>

#include <qwt_picker_machine.h>

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
    double** resArr_;
    void runThread(double arg, UsrParm strucArg, _dll_func func);

    void addPlot();
    void addPlotGrid();

    QwtPlotCurve *curve;
    QPolygonF points;
    void addCurve();

    void enableMagnifier();
    void enableMovingOnPlot();

    void enablePicker();
};

#endif // MAINWINDOW_H
