#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QFont>
#include <QDate>
#include <QTime>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("数字时钟");
    time = new QTimer(this);
    //每 1s 刷新屏幕 ，间接调用paintEvent事件
    connect(time, SIGNAL(timeout()), this, SLOT(update()));
    createRightPopActions();
    init();
    time->start(1000);
}
Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter back(this);
    back.drawPixmap(0,0,QPixmap("back.jpg"));
    QFont font;
    double rotate;      //每次旋转角度
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime dateTime = QDateTime::currentDateTime();

    /******字体设置******/
    font.setPointSize(12);		//字体大小
    font.setFamily("楷体");		//字体
    /******文字设置******/
    back.setPen(Qt::white);		//设置 字体颜色
    back.setFont(font);			//设置 字体
    /******范围设置******/
    back.setRenderHint(QPainter::Antialiasing);					//防锯齿
    back.translate(this->width() / 2, this->height() / 2);		//设置中心
    int side = qMin(width(), height());							//定义一个边界,保证是圆形的
    back.scale(side / 1200.0, side / 1200.0);

    //开始画图
    //back.begin(this);
    /**********年份**********/
    back.drawText(QPoint(-50, 0), QString("二零一九年"));
    /**********月份**********/
    back.rotate((1 - date.month()) * 30);
    for (int i = 0; i < 12; i++)
    {
        if ((i + 1) == date.month())
        {
            back.drawText(QPoint(90, 0), strListDate[i]+QString("月"));
            back.rotate(30);
            continue;
        }
        back.drawText(QPoint(100, 0), strListDate[i]);
        back.rotate(30);
    }
    /**********日期**********/
    rotate = 360.0 / MaxDate(date.month());
    back.rotate((date.month() - 1) * 30);			//将角度置零
    back.rotate((1 - date.day())*rotate);			//调节使当前日期在x轴上

    for (int i = 0; i < (int)MaxDate(date.month()); i++)
    {
        if ((i + 1) == date.day())
        {
            back.drawText(QPoint(150, 0), strListDate[i] + QString("号"));
            back.rotate(rotate);
            continue;
        }
        back.drawText(QPoint(150, 0), strListDate[i]);
        back.rotate(rotate);
    }
    /**********星期**********/
    back.rotate((date.day() - 1)*rotate);			//将角度置零
    QString tempStr = dateTime.toString().left(2);	//找到周 *
    back.rotate(-Week(tempStr, strListWeek)*360.0 / 7.0);	//逆时针旋转
    for (int i = 0; i < 7; i++)
    {
        back.drawText(QPoint(210, 0), strListWeek[i]);
        back.rotate(360.0/7.0);
    }
    /**********状态**********/
    double initRotate;										//状态
    back.rotate(Week(tempStr, strListWeek)*360.0 / 7.0);	//将角度置零
    if (time.hour() >= 6 && time.hour() < 12)	initRotate = 0;
    if (time.hour() >= 12 && time.hour() < 14)	initRotate = -1;
    if (time.hour() >= 14 && time.hour() < 19)	initRotate = -2;
    if (time.hour() >= 19 || time.hour() < 6)	initRotate = -3;
    back.rotate(initRotate * 90);				//初始化状态
    for (int i = 0; i < 4; i++)
    {
        back.drawText(QPoint(280, 0), strListState[i]);
        back.rotate(90);
    }
    /**********小时**********/
    back.rotate(-initRotate * 90);				//将角度置零
    back.rotate((1-time.hour()) * 30);			//初始化状态
    for (int i = 0; i < 12; i++)
    {
        if (time.hour() == (i + 1) || (time.hour() - 12) == (i + 1))
        {
            back.drawText(QPoint(390, 0), strListDate[i] + QString("点"));
            back.rotate(30);
            continue;
        }
        back.drawText(QPoint(390, 0), strListDate[i]);
        back.rotate(30);
    }
    /**********分钟**********/
    back.rotate((-1 + time.hour()) * 30);			//返回旋转前的角度
    back.rotate((1 - time.minute()) * 6);			//初始化状态
    for (int i = 0; i < 60; i++)
    {
        if (time.minute() == (i + 1))
        {
            back.drawText(QPoint(450, 0), strListDate[i]+QString("分"));
            back.rotate(6);
            continue;
        }
        back.drawText(QPoint(450, 0), strListDate[i]);
        back.rotate(6);
    }
    /**********秒钟**********/
    back.rotate((time.minute() - 1) * 6);					//返回旋转前的角度
    back.rotate((1 - time.second()) * 6);					//初始化状态
    for (int i = 0; i < 60; i++)
    {
        if (time.second() == (i + 1))
        {
            back.drawText(QPoint(530, 0), strListDate[i] + QString("秒"));
            back.rotate(6);
            continue;
        }
        back.drawText(QPoint(530, 0), strListDate[i]);
        back.rotate(6);
    }

    //back.end();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (this->isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    popMenu->clear();
    popMenu->addAction(adjustTimeAction);
    popMenu->addAction(adjustDateAction);
    popMenu->addSeparator();   //插入分割线
    popMenu->addAction(quitAction);
    //popMenu->exec(); //堵住
    popMenu->exec(QCursor::pos());
}

double Widget::MaxDate(int m)
{
    switch (m)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31.0;
        break;
    }
    return 30.0;
}

int Widget::Week(QString str, QStringList list)
{
    for (int i = 0; i < 7; i++)
    {
        if (str == list[i])
        {
            return i;
        }
    }
    return 0;
}

void Widget::createRightPopActions()
{
    popMenu = new QMenu(this);
    popMenu->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

    adjustTimeAction = new QAction(this);
    adjustTimeAction->setText(QStringLiteral("调整时间"));

    adjustDateAction = new QAction(this);
    adjustDateAction->setText(QStringLiteral("调整日期"));

    quitAction = new QAction(this);
    quitAction->setText(QStringLiteral("退出"));

    connect(quitAction, SIGNAL(triggered(bool)),   //关联退出信号
            this, SLOT(close()));
}

void Widget::init()
{
    /***************加载状态****************/
    strListState.append(QString("上午"));
    strListState.append(QString("中午"));
    strListState.append(QString("下午"));
    strListState.append(QString("晚上"));
    /***************加载星期****************/
    strListWeek.append(QString("周一"));
    strListWeek.append(QString("周二"));
    strListWeek.append(QString("周三"));
    strListWeek.append(QString("周四"));
    strListWeek.append(QString("周五"));
    strListWeek.append(QString("周六"));
    strListWeek.append(QString("周日"));
    /***************加载日期****************/
    strListDate.append(QString("一"));
    strListDate.append(QString("二"));
    strListDate.append(QString("三"));
    strListDate.append(QString("四"));
    strListDate.append(QString("五"));
    strListDate.append(QString("六"));
    strListDate.append(QString("七"));
    strListDate.append(QString("八"));
    strListDate.append(QString("九"));
    strListDate.append(QString("十"));
    strListDate.append(QString("十一"));
    strListDate.append(QString("十二"));
    strListDate.append(QString("十三"));
    strListDate.append(QString("十四"));
    strListDate.append(QString("十五"));
    strListDate.append(QString("十六"));
    strListDate.append(QString("十七"));
    strListDate.append(QString("十八"));
    strListDate.append(QString("十九"));
    strListDate.append(QString("二十"));
    strListDate.append(QString("二十一"));
    strListDate.append(QString("二十二"));
    strListDate.append(QString("二十三"));
    strListDate.append(QString("二十四"));
    strListDate.append(QString("二十五"));
    strListDate.append(QString("二十六"));
    strListDate.append(QString("二十七"));
    strListDate.append(QString("二十八"));
    strListDate.append(QString("二十九"));
    strListDate.append(QString("三十"));
    strListDate.append(QString("三十一"));
    strListDate.append(QString("三十二"));
    strListDate.append(QString("三十三"));
    strListDate.append(QString("三十四"));
    strListDate.append(QString("三十五"));
    strListDate.append(QString("三十六"));
    strListDate.append(QString("三十七"));
    strListDate.append(QString("三十八"));
    strListDate.append(QString("三十九"));
    strListDate.append(QString("四十"));
    strListDate.append(QString("四十一"));
    strListDate.append(QString("四十二"));
    strListDate.append(QString("四十三"));
    strListDate.append(QString("四十四"));
    strListDate.append(QString("四十五"));
    strListDate.append(QString("四十六"));
    strListDate.append(QString("四十七"));
    strListDate.append(QString("四十八"));
    strListDate.append(QString("四十九"));
    strListDate.append(QString("五十"));
    strListDate.append(QString("五十一"));
    strListDate.append(QString("五十二"));
    strListDate.append(QString("五十三"));
    strListDate.append(QString("五十四"));
    strListDate.append(QString("五十五"));
    strListDate.append(QString("五十六"));
    strListDate.append(QString("五十七"));
    strListDate.append(QString("五十八"));
    strListDate.append(QString("五十九"));
    strListDate.append(QString("零"));
}
