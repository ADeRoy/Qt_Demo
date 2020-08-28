#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include"mythread.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"main a.exec() :"<<QThread::currentThreadId();
    MyThread thread1,thread2;
    thread1.start();
    thread2.start();
    return a.exec();
}
