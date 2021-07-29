#include "widget.h"
#include "ui_widget.h"
#include "ToolBoxPow.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->widget->AddGroup("我的好友");
    ui->widget->AddGroup("家人");
    ui->widget->AddGroup("公众号");

    ui->widget->AddQQWidget("我的好友","徐大鹏",":/blownbear.jpg");
    ui->widget->AddQQWidget("我的好友","梦凡1号",":/dog.jpg");
    ui->widget->AddQQWidget("我的好友","徐大鹏1号",":/duolaameng.jpg");
    ui->widget->AddQQWidget("我的好友","徐大鹏",":/haimianbob.jpg");

    ui->widget->AddQQWidget("家人","马化腾",":/icebear.jpg");
    ui->widget->AddQQWidget("家人","马云",":/tom.jpg");
    ui->widget->AddQQWidget("家人","任正非",":/xiaoxin.jpg");
    ui->widget->AddQQWidget("家人","雷军",":/haimianbob.jpg");

    ui->widget->AddQQWidget("公众号","编程学习基地",":/bianchenxuexijidi.jpg");
    ui->widget->AddQQWidget("公众号","果果小师弟",":/duolaameng.jpg");
    ui->widget->AddQQWidget("公众号","码农有道",":/tom.jpg");
    ui->widget->AddQQWidget("公众号","字节流动",":/xiaoxin.jpg");

    QPushButton* button = new QPushButton;
    button->setText("自定义Widget");
    ui->widget->AddWidget("我的好友",button);
}

Widget::~Widget()
{
    delete ui;
}

