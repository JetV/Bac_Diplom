#ifndef CTWORKER_H
#define CTWORKER_H

#include <QObject>
#include <QDebug>


struct UsrParm {
    double InitVal;
    double TmSec;
    double Stp;
    int BdyNum;
    double FrcyCoeff;
    double AmpCoeff;
    double LftEdge;
    double RgtEdge;
    int PlotType;
};



typedef double (*_dll_func)(double, UsrParm, double** &);



class CTWorker : public QObject
{
    Q_OBJECT
public:
    explicit CTWorker(double arg, UsrParm strucArg, _dll_func func, double* result, double*** resArr, QObject *parent = 0);
    ~CTWorker();
    double result() const;

private:
    double arg_;
    double* result_;
    _dll_func func_;
    UsrParm strucArg_;
    double** resArr_;

signals:
    void finished();

public slots:
    void process();

};

#endif // CTWORKER_H
