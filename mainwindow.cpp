#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

    QLibrary library("C:\\Qt\\sinus\\sincalc-build\\Release\\release\\sincalc.dll");
    this->getFun = (_dll_func)library.resolve("SinCalc");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{


    double operand = this->ui->lineEdit->text().toDouble();

    double result = this->getFun(operand);

    this->ui->lineEdit_2->setText(QString::number(result));

}
