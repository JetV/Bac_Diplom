#include "ctworker.h"
#include <QThread>


CTWorker::CTWorker(double arg, UsrParm strucArg, _dll_func func, double* result, QObject *parent) :
    QObject(parent), arg_(arg)
{
    func_ = func;
    result_ = result;

    //UsrParm *strucArg_ = new UsrParm;
    strucArg_ = strucArg;
}

CTWorker::~CTWorker()
{
}

void CTWorker::process()
{

    *result_ = func_(arg_, strucArg_);
    qDebug () << "Yes, I'm here!, result:" << *result_;
    emit finished();
}
