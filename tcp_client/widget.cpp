#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Client");
    socket = new QTcpSocket;
    socketState = false;

    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnectedSlot()));     //客户端断开连接
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyReadSlot()));           //接收消息
}

Widget::~Widget()
{
    delete ui;
}

/*      开始连接        */
void Widget::on_pushButtonConnect_clicked()
{
    QString ipAddressStr = ui->lineEditAddress->text();
    quint16 port = ui->lineEditPort->text().toInt();

    if(!socketState)
    {
        socket->connectToHost(ipAddressStr, port);
        if(socket->waitForConnected(3000))
        {
            qDebug() << "Connect2Server OK";
            ui->pushButtonConnect->setText("断开连接");
            socketState = true;
        }
        else
        {
            qDebug() << socket->errorString();
            return;
        }
    }
    else
    {
        socket->close();    //触发disconnected()信号
        ui->pushButtonConnect->setText("连接");
        socketState = false;
    }
}

void Widget::disconnectedSlot()
{
    qDebug()<<"Socket close";
}

void Widget::readyReadSlot()
{
    QByteArray dataBa = socket->readAll();

    QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd")) +
            ":Recv\n" + str.fromLocal8Bit(dataBa.data());    //本地GBK转Unicode 解决乱码
    ui->textBrowserRecv->append(QString(str));          //送显示
}

void Widget::on_pushButtonSend_clicked()
{
    QString dataStr = ui->textEditSend->toPlainText();
    //QByteArray data = dataStr.toUtf8();        //发送UTF编码数据
    QByteArray data = dataStr.toLocal8Bit();     //发送本地字符(GBK)

    if(socket->isOpen() && socket->isValid())
    {
        socket->write(data);
    }

    QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd")) +
            ":Send\n" + str.fromLocal8Bit(data.data());    //本地GBK转Unicode 解决乱码
    ui->textBrowserRecv->append(QString(str));          //送显示
}
