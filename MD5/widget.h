#ifndef WIDGET_H
#define WIDGET_H

#include <QClipboard>
#include <QThread>
#include <QWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>

#include "Md5Check/md5check.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void ValInit();

signals:
    void checkMd5SumSignal(const QString &filePath);

private slots:
    void recvMd5CheckSumSlot(QByteArray);
    void recvProgressBarSlot(int,int);

    void on_pushButton_clicked();

    void on_clipboard_button_clicked();

private:
    Ui::Widget *ui;

    QThread md5Thread;          //线程
    Md5Check mMd5CheckSum;
    QClipboard* clip;          //剪切板
};

#endif // WIDGET_H
