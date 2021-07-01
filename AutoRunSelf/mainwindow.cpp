#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QTextCodec>
#include <QtDebug>

//开机启动注册表
#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    *
    * 系统托盘
    *
    */
    minimizeAction = new QAction(tr("最小化"), this);
    minimizeAction->setIcon(QIcon(":/test.ico"));	//设置ico
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("退出"), this);
    maximizeAction->setIcon(QIcon(":/test.ico"));
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(close()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIcon = new QSystemTrayIcon(this);
    /*将之前加载的菜单设置为系统托盘菜单*/
    trayIcon->setContextMenu(trayIconMenu);
    /* 设置托盘显示的图标。 */
    trayIcon->setIcon(QIcon(":/test.ico"));
    setWindowIcon(QIcon(":/test.ico"));
    /* 设置鼠标移动到托盘图标显示的文本。 */
    trayIcon->setToolTip("提示");
    trayIcon->show();

    /*
    *
    * 系统设置
    *
    */
    setting = new QButtonGroup(this);
    setting->addButton(ui->autoRunButton,0);
    setting->addButton(ui->setting_button,1);
    setting->setExclusive(false); //设置不互斥
    connect(setting, SIGNAL(buttonClicked(int)), this, SLOT(slot_CheckButton_checket(int)));
    read_ini();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_CheckButton_checket(int ButtonId)
{
    /*group修改，写入配置文件*/
    QCheckBox* temp = (QCheckBox*)setting->button(ButtonId);
    switch(ButtonId)
    {
    case 0:
        if(temp->isChecked())
        {
            SetAutoRun(true);
            qDebug()<<"开启：开机自启";
        }
        else {
            SetAutoRun(false);
            qDebug()<<"关闭：开机自启";
        }
        break;
    case 1:
        qDebug()<<"其他设置";
        break;
    }
    write_ini();
}

void MainWindow::write_ini()
{
    //打开配置文件
    QSettings *config = new QSettings("test.ini", QSettings::IniFormat);
    //设置编码方式
    config->setIniCodec(QTextCodec::codecForName("utf‐8"));
    //设置组group
    QString section=QString("setting/");        //一定要加/，否则读取会出问题
    config->beginGroup(section);                //设置组
    config->setValue(QString("%1").arg(setting->button(0)->text()),QString("%1").arg(setting->button(0)->isChecked()));
    config->setValue(QString("%1").arg(setting->button(1)->text()),QString("%1").arg(setting->button(1)->isChecked()));
    config->endGroup();
    delete config;
}

void MainWindow::read_ini()
{
    int value;
    //打开配置文件
    QSettings *config = new QSettings("test.ini", QSettings::IniFormat);
    //设置编码方式
    config->setIniCodec(QTextCodec::codecForName("utf‐8"));
    //设置组group
    QString section=QString("setting/");        //一定要加/，否则读取会出问题

    value = config->value(section + QString("%1").arg(setting->button(0)->text())).toInt();
    setting->button(0)->setChecked(value);

    value = config->value(section + QString("%1").arg(setting->button(1)->text())).toInt();
    setting->button(1)->setChecked(value);

    delete config;
}

void MainWindow::SetAutoRun(bool isAutoRun)
{
    QString  strApplicationName = QApplication::applicationName();              //获取应用名称
    QSettings * settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);

    if(isAutoRun)
    {
        QString strApplicationFilePath = QApplication::applicationFilePath();   //找到应用的目录
        settings->setValue(strApplicationName, strApplicationFilePath.replace("/", "\\"));//写入注册表
    }
    else
        settings->remove(strApplicationName);
}

