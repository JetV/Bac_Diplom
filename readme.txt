Изначально основной класс-ворекер для использования многопоточности имел вид:

class CTWorker : public QObject
{
    Q_OBJECT

public:
    CTWorker(int style);
    ~CTWorker();
private:
    Calc* cl;


public slots:
    void process();
    void stop();

signals:
    void finished();
};

Но потом я удалил отдельно созданный для него .h-файл и добавил группу класса из мастреа создания классов.
Получился конструктор класса следующего вида:
explicit CTWorker(QObject *parent = 0);
