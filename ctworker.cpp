#include "ctworker.h"
#include <QThread>


CTWorker::CTWorker(double arg, UsrParm strucArg, _dll_func func, double* result, double ***resArr, QObject *parent) :
    QObject(parent), arg_(arg)
{
    func_ = func;
    result_ = result; //Получение внешнего по отношщению к конструктору адреса в конструкторе
    strucArg_ = strucArg;
    resArr_ = *resArr;
}

CTWorker::~CTWorker()
{
}

void CTWorker::process()
{

    *result_ = func_(arg_, strucArg_, resArr_);

    qDebug () << "Yes, I'm here!, result:" << *result_;
    emit finished();
}
