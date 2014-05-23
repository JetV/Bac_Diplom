#ifndef CTWORKER_H
#define CTWORKER_H

#include <QObject>
#include <QDebug>



//struct UsrParm {
//    double InitVal = 0;
//    double TmSec = 1;
//    double Stp = 0.1;
//    int BdyNum = 15;
//    double PhsCoeff = 5.1;
//    double AmpCoeff = 1;
//    int PlotType = 0;
//} strucArg;

struct UsrParm {
    double InitVal;
    double TmSec;
    double Stp;
    int BdyNum;
    double PhsCoeff;
    double AmpCoeff;
    int PlotType;
};



typedef double (*_dll_func)(double, UsrParm);



class CTWorker : public QObject
{
    Q_OBJECT
public:
    explicit CTWorker(double arg, UsrParm strucArg, _dll_func func, double* result, QObject *parent = 0);
    ~CTWorker();
    double result() const;

private:
    double arg_;
    double* result_;
    _dll_func func_;
    UsrParm strucArg_;


signals:
    void finished();


public slots:
    void process();

};

#endif // CTWORKER_H
