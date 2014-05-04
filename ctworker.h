#ifndef CTWORKER_H
#define CTWORKER_H

#include <QObject>
#include <QDebug>


class CTWorker : public QObject
{
    Q_OBJECT
public:
    explicit CTWorker(QObject *parent = 0);
    ~CTWorker();
private:
//    Calc* cl;
    void addThread();

signals:
    void finished();


public slots:
    void process();
    //void stop();

};

#endif // CTWORKER_H
