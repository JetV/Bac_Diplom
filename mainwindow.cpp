#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLibrary library("C:\\Qt\\sinus\\sincalc-build\\Release\\release\\sincalc.dll");
    this->getFun = (_dll_func)library.resolve("SinCalc");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runThread(double arg, UsrParm strucArg, _dll_func func)
{
    worker_ = new CTWorker(arg, strucArg, func, &result_);
    thread_ = new QThread;
    worker_->moveToThread(thread_);

    connect(thread_, SIGNAL(started()), worker_, SLOT(process()));
    connect(worker_, SIGNAL(finished()), thread_, SLOT(quit()));
    connect(worker_, SIGNAL(finished()), this, SLOT(ready()));
    connect(thread_, SIGNAL(finished()), thread_, SLOT(deleteLater()));
    thread_->start();
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void MainWindow::ready()
{
    ui->lineEdit_2->setText(QString::number(result_));

    ui->plainTextEdit->appendPlainText(QString::number(result_));
    worker_->deleteLater();
}


void MainWindow::on_pushButton_clicked()
{
    double arg = this->ui->lineEdit->text().toDouble();
    strucArg_.AmpCoeff = this->ui->AmpCoeff->text().toDouble();
    strucArg_.BdyNum = this->ui->BdyNum->text().toInt();
    strucArg_.InitVal = this->ui->InitVal->text().toDouble();
    strucArg_.PhsCoeff = this->ui->PhsCoeff->text().toDouble();
    strucArg_.PlotType = 0;
    strucArg_.Stp = this->ui->Stp->text().toDouble();
    strucArg_.TmSec = this->ui->TmSec->text().toDouble();

    runThread(arg, strucArg_, getFun);
}
