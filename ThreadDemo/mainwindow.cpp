#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(100);   //设置进度条最大值
    ui->progressBar->setValue(0);       //设置进度条当前值为0
    ui->statusBar->addWidget(ui->progressBar);  //将进度条添加进状态栏MainToolBal

    m_ProgressBarVal.moveToThread(&m_thread);   //m_ProgressBarVal移动到线程中去
    m_thread.start();                   //开启线程
    //关联信号，当触发checkMyThread()信号时执行MyThreadWork()函数
    connect(this,SIGNAL(checkMyThread()),&m_ProgressBarVal,SLOT(MyThreadWork()));
    //关联信号，当触发SendVal()信号时执行RecvVal()函数，并将值传递过去
    connect(&m_ProgressBarVal,SIGNAL(SendVal(int)),this,SLOT(RecvVal(int)));
}

MainWindow::~MainWindow()
{
    //线程退出并等待10s
    m_thread.exit();
    m_thread.wait(1000*10);
    delete ui;
}
void MainWindow::RecvVal(int Val)
{
    //设置进度条的值
    ui->progressBar->setValue(Val);
}

void MainWindow::on_pushButton_clicked()
{
    //触发checkMyThread()信号，使MyThreadWork()工作
    emit checkMyThread();
}
