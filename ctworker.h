#ifndef CTWORKER_H
#define CTWORKER_H

#include <QObject>
#include <QDebug>

typedef double (*_dll_func)(double);

class CTWorker : public QObject
{
    Q_OBJECT
public:
    explicit CTWorker(double arg, _dll_func func, double* result, QObject *parent = 0);
    ~CTWorker();
    double result() const;

private:
    double arg_;
    double* result_;
    _dll_func func_;

signals:
    void finished();


public slots:
    void process();

};

#endif // CTWORKER_H
