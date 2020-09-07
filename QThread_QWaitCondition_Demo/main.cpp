/******************************************************************************

                  版权所有 (C), 2001-2011, DeRoy

 ******************************************************************************
  文 件 名   : main.cpp
  版 本 号   : 初稿
  作    者   : DeRoy
  生成日期   : 2020年9月7日
  最近修改   :
  功能描述   : Tcp_Server
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2020年9月7日
    作    者   : DeRoy
    修改内容   : 创建文件
	
	微信公众号：编程学习基地

******************************************************************************/

#include <QtCore/QCoreApplication>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QDebug>
#define BUFFER_SIZE 2

/*生产者*/
class producons
{
public:
    int buffer[BUFFER_SIZE];    /*数据*/
    QMutex lock;                //互斥锁
    int readpos,writepos;       //读写位置
    QWaitCondition nottempty;   //条件变量  没有空间
    QWaitCondition notfull;     //条件变量  没有货物

    producons()
    {
        readpos = writepos = 0;
    }
};
producons buffer;    //生产者对象

class Producor:public QThread
{
public:
    void run();
    void put(producons * prod,int data);
};

void Producor::run()
{
    int n;
    for(n = 0;n<5;n++)
    {
        qDebug()<<"生产者睡眠 1s...";
        sleep(1);
        qDebug()<<"生产信息:" << n;
        put(&buffer, n);
    }
    for(n=5; n<10; n++)
    {
        qDebug()<<"生产者睡眠 3s...";
        sleep(3);
        qDebug()<<"生产信息："<< n;
        put(&buffer,n);
    }
    put(&buffer, -1);
    qDebug()<<"结束生产者!\n";
    return;
}
void Producor::put(producons *prod, int data)
{
    prod->lock.lock();

    //write until buffer not full
    while((prod->writepos + 1)%BUFFER_SIZE == prod->readpos)
    {
        qDebug()<<"生产者等待生产，直到buffer有空位置";
        prod->notfull.wait(&prod->lock);
    }
    //将数据写入到buffer里面去
    prod->buffer[prod->writepos] = data;
    prod->writepos++;
    if(prod->writepos >= BUFFER_SIZE)
        prod->writepos = 0;
    //仓库已满，等待消费者消费
    prod->nottempty.wakeAll();
    prod->lock.unlock();
}

class Consumer:public QThread
{
public:
    void run();
    int get(producons *prod);
};

void Consumer::run()
{
    int d = 0;
    while(1)
    {
        qDebug()<<"消费者睡眠 2s...";
        sleep(2);
        d = get(&buffer);
        qDebug()<<"读取信息:"<< d;
        if(d == -1) break;
    }
    qDebug()<<"结束消费者!";
    return;
}

int Consumer::get(producons *prod)
{
    int data;
    prod->lock.lock();      //加锁

    while(prod->writepos == prod->readpos)
    {
        qDebug()<<"消费者等待，直到buffer有消息\n";
        prod->nottempty.wait(&prod->lock);
    }
    //读取buffer里面的消息
    data = prod->buffer[prod->readpos];
    prod->readpos++;

    if(prod->readpos >=BUFFER_SIZE)
        prod->readpos = 0;
    //触发非满条件变量 告诉生产者可以生产
    prod->notfull.wakeAll();
    prod->lock.unlock();

    return data;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Producor productor;
    Consumer consumer;
    productor.start();
    consumer.start();
    productor.wait();
    consumer.wait();
    return a.exec();
}
