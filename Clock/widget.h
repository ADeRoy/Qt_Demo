#ifndef WIDGET_H
#define WIDGET_H

#include <QMenu>
#include <QTimer>
#include <QWidget>
#include <QAction>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QStringList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

private:
    QTimer* time;		//定时器
    QMenu *popMenu;     //右键弹出式菜单
    QAction *adjustTimeAction;    //右键弹出式菜单中的内容 调整时间
    QAction *adjustDateAction;    //调整日期
    QAction *quitAction;          //退出
    QStringList strListDate, strListState, strListWeek;
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);	//右键弹出菜单

private:
    double MaxDate(int m);
    int Week(QString str,QStringList list);
    void createRightPopActions();  //创建右键菜单
    void init();

};

#endif // WIDGET_H
