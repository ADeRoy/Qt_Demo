#include "widget.h"
#include "ui_widget.h"
#include <windows.h>
#include <QButtonGroup>
#include <QtDebug>
#include <QSystemTrayIcon>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    WidgetValInit();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    if(isHide)
    {
        this->hide();
        Sleep(200);
    }
    emit SrceenBegin();
    srceenWidget->show();
    srceenWidget->showFullScreen();
}

void Widget::slot_RadioButton_checket(int id)
{
    QRadioButton* temp = (QRadioButton*)radioGroup->button(id);
    switch(id)
    {
    case 0:
        if(temp->isChecked())
        {
            isHide = true;
        }
        else {
            isHide = false;
        }
        break;
    case 1:
        break;
    }
}

void Widget::WidgetValInit()
{
    quitAction = new QAction(tr("退出"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    screenShotAction = new QAction(tr("截图"), this);
    screenShotAction->setIcon(QIcon(":/src/screenshot.png"));
    connect(screenShotAction, SIGNAL(triggered()), this, SLOT(on_pushButton_clicked()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(screenShotAction);
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);

    /*将之前加载的菜单设置为系统托盘菜单*/
    trayIcon->setContextMenu(trayIconMenu);
    /* 设置托盘显示的图标。 */
    trayIcon->setIcon(QIcon(":/src/apple.ico"));
    setWindowIcon(QIcon(":/src/apple.ico"));
    /* 设置鼠标移动到托盘图标显示的文本。 */
    trayIcon->setToolTip("截图");
    /*截图*/
    srceenWidget = new Srceen;
    connect(this,SIGNAL(SrceenBegin()),srceenWidget,SLOT(GetWindowSrceen()));

    radioGroup = new QButtonGroup(this);
    radioGroup->setExclusive(false);   //重点    设置不互斥
    radioGroup->addButton(ui->radioButton,0);
    radioGroup->addButton(ui->anotherRadioButton,1);
    connect(radioGroup, SIGNAL(buttonClicked(int)), this,SLOT(slot_RadioButton_checket(int)));
    isHide = true;
}
