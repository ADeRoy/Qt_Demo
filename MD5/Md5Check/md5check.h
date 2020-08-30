#ifndef MD5CHECK_H
#define MD5CHECK_H

#include <QObject>
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

class Md5Check : public QObject
{
    Q_OBJECT
public:
    explicit Md5Check(QObject *parent = nullptr);

signals:
    void sendMd5CheckSumSignal(QByteArray);         //反馈md5值到界面
    void sendProgressBarSignal(int, int);           //反馈进度到界面 以生成进度条
    //已经处理的数据量 待处理的总量

public slots:
    void getMd5CheckSumSlot(const QString &filePath);
};

#endif // MD5CHECK_H
