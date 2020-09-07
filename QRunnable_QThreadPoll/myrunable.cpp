#include "myrunable.h"


MyRunable::MyRunable(QObject *parent) : QObject(parent)
{

}

MyRunable::~MyRunable()
{
    qDebug()<<"delete Task";
}

void MyRunable::run()
{
    int i = 10;
    while(i--)
    {
        qDebug() << "线程id："<< QThread::currentThreadId()<< QString(":剩余%1").arg(i);
        QThread::sleep(1);
    }
}
