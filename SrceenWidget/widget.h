#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QPushButton>
#include "srceen.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    void SrceenBegin();             //给srceenWidget发送开始截图信号
private slots:
    void on_pushButton_clicked();
private slots:
    void slot_RadioButton_checket(int);
private:
    void WidgetValInit();

private:
    Ui::Widget *ui;
    Srceen* srceenWidget;
    QButtonGroup* radioGroup;
    bool isHide;    //是否隐藏当前窗口

    QSystemTrayIcon *trayIcon;  //系统托盘
    QMenu *trayIconMenu;        //菜单
    QAction *quitAction;        //退出
    QAction *screenShotAction;  //截图
};

#endif // WIDGET_H
