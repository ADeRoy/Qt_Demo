#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>
#include <QMutex>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
protected:
    virtual void run();
private:
};
#endif // MYTHREAD_H
