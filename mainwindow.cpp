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


    // Создать поле со шкалами для отображения графика
    addPlot();

    // Включить масштабную сетку
    addPlotGrid();

    // Кривая
    addCurve();

    // Включить возможность приближения/удаления графика
    enableMagnifier();

    // Включить возможность перемещения по графику
    enableMovingOnPlot();

    // Включить отображение координат курсора и двух перпендикулярных
    // линий в месте его отображения
    enablePicker();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runThread(double arg, UsrParm strucArg, _dll_func func)
{
    worker_ = new CTWorker(arg, strucArg, func, &result_, &resArr_);
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

    qDebug() << "arr[0]" << *resArr_;
    worker_->deleteLater();
}


void MainWindow::on_pushButton_clicked()
{
    double arg = this->ui->lineEdit->text().toDouble();
    strucArg_.AmpCoeff = this->ui->AmpCoeff->text().toDouble();
    strucArg_.BdyNum = this->ui->BdyNum->text().toInt();
    strucArg_.InitVal = this->ui->InitVal->text().toDouble();
    strucArg_.FrcyCoeff = this->ui->PhsCoeff->text().toDouble();
    strucArg_.LftEdge = 0; //TODO! Передача в функцию правильной длины и типа графика
    strucArg_.RgtEdge = 0;
    strucArg_.PlotType = 0;
    strucArg_.Stp = this->ui->Stp->text().toDouble();
    strucArg_.TmSec = this->ui->TmSec->text().toDouble();   

    runThread(arg, strucArg_, getFun);
}








void MainWindow::addPlot()
{
    // #include <qwt_plot.h>
    ui->Qwt_Widget->setTitle( "Qwt demonstration" );
    ui->Qwt_Widget->setCanvasBackground( Qt::white );

    // Параметры осей координат
    ui->Qwt_Widget->setAxisTitle(QwtPlot::yLeft, "Y");
    ui->Qwt_Widget->setAxisTitle(QwtPlot::xBottom, "X");
    ui->Qwt_Widget->insertLegend( new QwtLegend() );

}

void MainWindow::addPlotGrid()
{
    // #include <qwt_plot_grid.h>
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen( Qt::gray, 0.3 )); // цвет линий и толщина
    grid->attach( ui->Qwt_Widget );
}

void MainWindow::addCurve()
{
    //#include <qwt_plot_curve.h>
    curve = new QwtPlotCurve();
    curve->setTitle( "Demo Curve" );
    curve->setPen( Qt::blue, 1 ); // цвет и толщина кривой

    // Маркеры кривой
    // #include <qwt_symbol.h>
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );

    // Добавить точки на ранее созданную кривую
    // Значения точек записываются в массив, затем считываются
    // из этого массива
    for (int i = 0; i < 5; i++) {
        points << QPointF( 1.0 * i, 1.0 * i); // произвольное заполнение
    }

    curve->setSamples( points ); // ассоциировать набор точек с кривой

    curve->attach( ui->Qwt_Widget ); // отобразить кривую на графике
}

void MainWindow::enableMagnifier()
{
    // #include <qwt_plot_magnifier.h>
    QwtPlotMagnifier *magnifier =
            new QwtPlotMagnifier(ui->Qwt_Widget->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
}

void MainWindow::enableMovingOnPlot()
{
    // #include <qwt_plot_panner.h>
    QwtPlotPanner *d_panner = new QwtPlotPanner( ui->Qwt_Widget->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
}

void MainWindow::enablePicker()
{
    // #include <qwt_plot_picker.h>
    // настройка функций
    QwtPlotPicker *d_picker =
            new QwtPlotPicker(
                QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
    QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
    QwtPicker::AlwaysOn, // всегда включен
    ui->Qwt_Widget->canvas() ); // ассоциация с полем

    // Цвет перпендикулярных линий
    d_picker->setRubberBandPen( QColor( Qt::red ) );

    // цвет координат положения указателя
    d_picker->setTrackerPen( QColor( Qt::black ) );

    // непосредственное включение вышеописанных функций
    d_picker->setStateMachine( new QwtPickerDragPointMachine() );
}
