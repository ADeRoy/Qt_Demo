/******************************************************************************

                  版权所有 (C), 2001-2011, DeRoy

 ******************************************************************************
  文 件 名   : main.cpp
  版 本 号   : 初稿
  作    者   : DeRoy
  生成日期   : 2020年9月7日
  最近修改   :
  功能描述   : QThreadPool_Demo
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2020年9月7日
    作    者   : DeRoy
    修改内容   : 创建文件

******************************************************************************/

#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include"myrunable.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<QThread::idealThreadCount();
    qDebug() << "main thread id: " << QThread::currentThreadId();
    QThreadPool::globalInstance()->setMaxThreadCount(15);   //设置线程池最大线程数量
    MyRunable* task = new MyRunable();
    task->setAutoDelete(true);          //autoDelete属性默认为true   QThreadPool会在run（）函数运行结束后，自动删除了MyTask对象
    QThreadPool::globalInstance()->start(task);             //任务放进线程池
    QThread::sleep(1);
    MyRunable* task1 = new MyRunable();
    task1->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task1);

    QThreadPool::globalInstance()->waitForDone();           //等待任务结束
    qDebug() << "end";
    return a.exec();
}
