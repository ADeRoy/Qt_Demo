#include "mythread.h"
#include <QDebug>
#include <QThread>
MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::MyThreadWork()
{
    qDebug()<<QThread::currentThreadId();
    for(int val=0;val<=100;val++)
    {
        //向外部发送信号
        emit SendVal(val);
        //睡眠一秒
        QThread::msleep(50);
        qDebug()<<val;
    }
}
