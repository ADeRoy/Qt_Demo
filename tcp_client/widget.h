#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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
    void on_pushButtonConnect_clicked();
    void disconnectedSlot();
    void readyReadSlot();
    void on_pushButtonSend_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
    bool socketState;
};

#endif // WIDGET_H
