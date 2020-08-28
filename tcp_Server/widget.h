#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_pushButton_listen_clicked();//开始监听
    void newConnectionSlot();           //新连接
    void disconnectedSlot();            //断开连接
    void readyReadSlot();               //接收消息的槽函数
    void on_pushButton_send_clicked();
private:
    void enumIpAddress();
private:
    Ui::Widget *ui;

    QTcpServer *mServer;
    QTcpSocket *mClient = nullptr;
    QList<QTcpSocket *>mClientList;
};

#endif // WIDGET_H
