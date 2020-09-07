/******************************************************************************

                  版权所有 (C), 2001-2011, DeRoy

 ******************************************************************************
  文 件 名   : myrunable.h
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


#ifndef MYRUNABLE_H
#define MYRUNABLE_H

#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QThread>

class MyRunable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyRunable(QObject *parent = nullptr);
    ~MyRunable();
protected:
    void run();
};

#endif // MYRUNABLE_H
