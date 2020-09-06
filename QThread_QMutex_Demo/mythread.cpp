#include "mythread.h"
#include <QDebug>
extern int global_Val;
extern QMutex globlMutex;   //锁一定是全局的
MyThread::MyThread()
{
    qDebug()<<"mainThread::currentId:"<<QThread::currentThreadId();
}

void MyThread::run()
{
    while (global_Val>0) {
        QMutexLocker locker(&globlMutex);
        qDebug()<<"threadId:"<< QThread::currentThreadId()<<"  global_val:"<<global_Val--;
//        QThread::msleep(200);
    }
    qDebug()<<"Task finish";
}
