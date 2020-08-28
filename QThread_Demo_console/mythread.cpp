#include "mythread.h"
#include <QtDebug>
MyThread::MyThread()
{
    qDebug()<<"MyThread::MyThread:"<<QThread::currentThreadId();
}

void MyThread::run()
{
    qDebug()<<"MyThread::run:"<<QThread::currentThreadId();
    int count = 100;
    do
    {
        qDebug()<<"count:"<<count--;
        QThread::sleep(1);
    }while (count>=0);
}
