#include "ctworker.h"
#include <QThread>


CTWorker::CTWorker(QObject *parent) :
    QObject(parent)
{
//    cl = NULL;
}

CTWorker::~CTWorker()
{
//    if (cl != NULL) {
//        delete cl;
//    }
}

void CTWorker::addThread()
{
    CTWorker* worker = new CTWorker(0);
    QThread* thread = new QThread;
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();

    return;

}

void CTWorker::process()
{
    qDebug("Yes, I'm here!");
    emit finished();
    return;
}

