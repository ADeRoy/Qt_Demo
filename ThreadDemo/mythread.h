#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

signals:
    //线程向外部发出带Val值得信号
    void SendVal(int);
public slots:
    //线程工作函数
    void MyThreadWork();
};

#endif // MYTHREAD_H
