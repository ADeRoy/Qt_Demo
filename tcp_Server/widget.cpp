#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");
    mServer = new QTcpServer;
    enumIpAddress();

    //处理新连接客户端
    connect(mServer, SIGNAL(newConnection()),this, SLOT(newConnectionSlot()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::enumIpAddress()
{
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    QStringList addressStrList;
    addressStrList.clear();

    for(int index = 0;index<ipList.size();index++)
    {
        if(ipList.at(index).isNull())   continue;                   //如果地址为空,则去掉
        QAbstractSocket::NetworkLayerProtocol protocol = ipList.at(index).protocol();
        if(protocol != QAbstractSocket::IPv4Protocol)   continue;   //只取IPV4的地址
        addressStrList.append(ipList.at(index).toString());
    }
    ui->comboBox_Address->addItems(addressStrList);
}

void Widget::on_pushButton_listen_clicked()
{
    QString serverAddressStr = ui->comboBox_Address->currentText();     //获取服务器ip地址
    quint16 port = ui->lineEdit_port->text().toInt();                   //获取服务器端口
    QHostAddress serverAddress = QHostAddress(serverAddressStr);        //初始化协议族

    if(mServer->isListening())
    {
        //在监听状态 取消监听
        mServer->close();
        ui->pushButton_listen->setText("监听");
    }
    else
    {
        //不在监听状态 开始监听
        if(mServer->listen(serverAddress, port))
        {
            //监听成功
            qDebug() << "Listen Ok!!";
            ui->pushButton_listen->setText("停止监听");
        }
        else
        {
            //监听失败
            QMessageBox::warning(this, "Tcp Server Listen Error", mServer->errorString());
        }
    }
}

void Widget::newConnectionSlot()
{
    qDebug()<<"new connect signal";
    QString clientInfo;

    mClient = mServer->nextPendingConnection();
    mClientList.append(mClient);
    //窥视Client 信息
    clientInfo = mClient->peerAddress().toString() + ":"+  QString::number(mClient->peerPort());
    ui->listWidget_client->addItem(clientInfo);

    connect(mClient, SIGNAL(readyRead()),this, SLOT(readyReadSlot()));          //接收消息
    connect(mClient, SIGNAL(disconnected()),this, SLOT(disconnectedSlot()));    //断开连接
}

void Widget::readyReadSlot()
{
    QByteArray recvArray;
    QTcpSocket* current = nullptr;
    if(!mClientList.isEmpty())
    {
        //接收客户端数据
        for(int index = 0;index < mClientList.count();index ++)
        {
            current = mClientList.at(index);

            if(current->isReadable())
            {
                recvArray = current->readAll();
                if(recvArray.isEmpty()) continue;
                QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd")) +
                        ":Recv\n" + str.fromLocal8Bit(recvArray.data());    //本地GBK转Unicode 解决乱码
                ui->textBrowser_recv->append(str);
                break;
            }
        }
        //转发给其他客户端
        for(int index = 0;index < mClientList.count();index ++)
        {
            QTcpSocket* temp = mClientList.at(index);
            if(current == temp) continue;
            if(temp->isWritable())
            {
                temp->write(recvArray);
            }
        }
    }

//    if(mClient!=nullptr)
//    {
//        if(mClient->isReadable())
//        {
//            QByteArray recvArray = mClient->readAll();
//            QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd")) +
//                    ":Recv\n" + str.fromLocal8Bit(recvArray.data());    //本地GBK转Unicode 解决乱码
//            ui->textBrowser_recv->append(str);
//        }
//    }
}

void Widget::disconnectedSlot()
{
    QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd"))
            + "client close..";
    ui->textBrowser_recv->append(str);
}

void Widget::on_pushButton_send_clicked()
{
    QString sendString = ui->plainTextEdit_send->toPlainText();
    QByteArray sendArr = sendString.toLocal8Bit();

    //群发给所有客户端连接
    if(!mClientList.isEmpty())
    {
        for(int index = 0;index < mClientList.count();index ++)
        {
            QTcpSocket* temp = mClientList.at(index);
            if(temp->isWritable())
            {
                temp->write(sendArr);
            }
        }
    }
    QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd"))
            + ":Send\n" + sendString;
    ui->textBrowser_recv->append(str);          //本地GBK转Unicode 解决乱码

//    //一对一发送，只会发送给最近的一个客户端连接
//    if(mClient!=nullptr)
//    {
//        if(mClient->isWritable())
//        {
//            QString sendString = ui->plainTextEdit_send->toPlainText();
//            QByteArray sendArr = sendString.toLocal8Bit();
//            mClient->write(sendArr);

//            QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd"))
//                    + ":Send\n" + sendString;
//            ui->textBrowser_recv->append(str);          //本地GBK转Unicode 解决乱码
//        }
    //    }
}

