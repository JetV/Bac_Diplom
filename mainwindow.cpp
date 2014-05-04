#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLibrary library("C:\\Users\\Sergey\\Desktop\\qtproject\\sincalc-build\\Release\\release\\sincalc.dll");
    this->getFun = (_dll_func)library.resolve("SinCalc");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runThread(double arg, _dll_func func)
{
    worker_ = new CTWorker(arg, func, &result_);
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
    worker_->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    double arg = this->ui->lineEdit->text().toDouble();
    runThread(arg, getFun);
}
