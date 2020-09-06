#include <QCoreApplication>
#include "mythread.h"
int global_Val = 100;
QMutex globlMutex;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyThread thread1,thread2;
    thread1.start();
    thread2.start();
    return a.exec();
}
