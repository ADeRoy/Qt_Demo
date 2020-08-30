#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(QString("MD5"));
    ValInit();
}

Widget::~Widget()
{
    md5Thread.exit();
    md5Thread.wait(10*1000);
    delete ui;
}

void Widget::ValInit()
{
    /*设置进度条进度为0*/
    ui->progressBar->setValue(0);
    /*将IO操作放到线程中去执行，防止文件过大卡界面*/
    mMd5CheckSum.moveToThread(&md5Thread);      /*从一个object 移动到 一个thread*/
    md5Thread.start();                          /*开启线程*/

    /*  绑定信号与槽  */
    /* 关联MD5计算槽函数 让Md5Check对象开始计算MD5值 */
    connect(this,SIGNAL(checkMd5SumSignal(QString)),&mMd5CheckSum,SLOT(getMd5CheckSumSlot(QString)));
    /*关联MD5结果返回信号，将MD5计算结果传递给Widget定义的槽函数recvMd5CheckSumSlot*/
    connect(&mMd5CheckSum, SIGNAL(sendMd5CheckSumSignal(QByteArray)),this, SLOT(recvMd5CheckSumSlot(QByteArray)));
    /*关联MD5计算进度，将进度返回给Widget定义的槽函数recvProgressBarSlot*/
    connect(&mMd5CheckSum, SIGNAL(sendProgressBarSignal(int,int)),this, SLOT(recvProgressBarSlot(int,int)));
}

void Widget::recvMd5CheckSumSlot(QByteArray result)
{
    ui->textEdit->setText(result);      /*将MD5计算结果显示到主界面*/
}

void Widget::recvProgressBarSlot(int total, int current)
{
    ui->progressBar->setMaximum(total);     /* 设置进度条最大值 */
    ui->progressBar->setValue(current);     /* 设置当前进度 */
}

void Widget::on_pushButton_clicked()
{
    QFileInfo MD5Fileinfo;              /* 文件信息 */
    QString md5Filename = QFileDialog::getOpenFileName(this,"open");

    MD5Fileinfo = QFileInfo(md5Filename);

    ui->lineEdit->clear();              /*清空Edit*/
    ui->textEdit->clear();
    if(MD5Fileinfo.exists())
    {
        ui->lineEdit->setText(MD5Fileinfo.fileName());
        emit checkMd5SumSignal(md5Filename);            /*将打开的文件路径通过信号传递给Md5Check对象*/
    }
}

void Widget::on_clipboard_button_clicked()
{
    clip = QApplication::clipboard();           /*获取系统剪贴板*/
    clip->setText(ui->textEdit->toPlainText()); /*设置系统剪贴板内容*/
}
