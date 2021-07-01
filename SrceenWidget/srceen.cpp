#include "srceen.h"

#include <QGuiApplication>
#include <QPainter>
#include <QWindow>
#include <QDebug>
#include <QFileDialog>
#include <QTime>

Srceen::Srceen(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);      //去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);   //设置背景透明
    SrceenValInit();
}

void Srceen::paintEvent(QPaintEvent *)
{   
    QPixmap pix(originalPixmap.width(), originalPixmap.height());
    pix.fill((QColor(0, 0, 0, 120)));       //阴影颜色设置;
    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);

    QFont font;
    font.setPointSize(12);
    painter.setFont(font);

    painter.drawPixmap(0,0,originalPixmap);
    painter.drawPixmap(0,0,pix);    //画一层阴影

    /*      绘制截图区域        */
    if(rectangle.height()!=0||rectangle.width()!=0)
    {
        if(rectangle.height()<0 && rectangle.width()>0)
        {
            //绘制用户截图区域  鼠标在起点的右上方
            screenRect.setRect(rectangle.x(),rectangle.y()+rectangle.height(),rectangle.width(),qAbs(rectangle.height()));
        }
        else if (rectangle.width()<0 && rectangle.height()>0) {
            //绘制用户截图区域  鼠标在起点的左下方
            screenRect.setRect(rectangle.x() + rectangle.width(),rectangle.y(),qAbs(rectangle.width()),rectangle.height());
        }
        else if (rectangle.height()< 0 && rectangle.width()<0) {
            //绘制用户截图区域  鼠标在起点的左上方
            screenRect.setRect(rectangle.x()+rectangle.width(),rectangle.y()+rectangle.height(),qAbs(rectangle.width()),qAbs(rectangle.height()));
        }
        else if(rectangle.height()> 0 && rectangle.width()>0){
            //绘制用户截图区域  鼠标在起点的右下方
            screenRect.setRect(rectangle.x(),rectangle.y(),rectangle.width(),rectangle.height());
        }
        painter.drawPixmap(screenRect.x(),screenRect.y(),originalPixmap.copy(screenRect));
        painter.drawRect(rectangle);

        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(screenRect.x() + 2, screenRect.y() - 8, QString("%1 x %2").arg(screenRect.width()).arg(screenRect.height()));

        /*放大图*/
        QPixmap endPointImage = originalPixmap.copy(mousePos.x() - 25
                                                    ,mousePos.y() - 25,50,50).scaled(100, 100);
        //放大矩形区域
        enlargeRect.setRect(mousePos.x() + 32,mousePos.y() + 22,100,100);
        //绘制放大矩形区域
        painter.drawPixmap(enlargeRect.x(),enlargeRect.y(), endPointImage);
        //绘制十字坐标
        pen.setColor(Qt::green);
        painter.setPen(pen);
        //横线
        painter.drawLine(enlargeRect.x(),enlargeRect.y() + enlargeRect.height()/2,
                         enlargeRect.x() + enlargeRect.width(),enlargeRect.y() + enlargeRect.height()/2);
        //竖线
        painter.drawLine(enlargeRect.x() + enlargeRect.width()/2,enlargeRect.y(),
                         enlargeRect.x() + enlargeRect.width()/2,enlargeRect.y() + enlargeRect.height());
        //方块
        painter.drawRect(enlargeRect);
        //文字
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(enlargeRect.x(), enlargeRect.y() + enlargeRect.height()+ 16, QString("POS:(%1,%2)").arg(enlargeRect.x()).arg(enlargeRect.y()));

    }
    else {
        painter.drawRect(originalPixmap.rect());    //给全屏边框绘制绿色矩形框
    }
}

void Srceen::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键按下，设置截图起点
    if (event->button() == Qt::LeftButton)
    {
        rectangle.setRect(event->x(),event->y(),0,0);
    }
}

void Srceen::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void Srceen::mouseMoveEvent(QMouseEvent *event)
{
    mousePos.setX(event->x());
    mousePos.setY(event->y());
    if(rectangle.x()!=-1||rectangle.y()!=-1)
    {
        rectangle.setHeight(event->y()-rectangle.y());
        rectangle.setWidth(event->x()-rectangle.x());
    }
    this->update();
}

//右键菜单
void Srceen::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)
    RightButtonMenu->clear();
    RightButtonMenu->addAction(saveSreenShot);
    RightButtonMenu->addAction(saveCopyAs);
    RightButtonMenu->addSeparator();    //分割线
    RightButtonMenu->addAction(quitSreenShot);
    RightButtonMenu->exec(QCursor::pos());  //在当前鼠标处堵住
}

//获取桌面截图
void Srceen::GetWindowSrceen()
{
    screen = QGuiApplication::primaryScreen(); //获取屏幕图像
    originalPixmap = screen->grabWindow(0);
    rectangle.setRect(0,0,0,0);
}

//保存截图
void Srceen::SaveSrceenShot()
{
    clip = QApplication::clipboard();
    clip->setPixmap(originalPixmap.copy(screenRect));   //保存到粘贴板
    this->hide();
    rectangle.setRect(0,0,0,0);
}

//图片另存为
void Srceen::SaveCopyAs()
{
    QDateTime current_time = QDateTime::currentDateTime();
    //显示时间，格式为：年-月-日
    QString StrCurrentTime = current_time.toString("yyyy-MM-dd");

    QString fileName = QFileDialog::getSaveFileName(this,"保存文件",StrCurrentTime,
                                                    tr("Image Files (*.png);;Image Files (*.jpg);;Image Files (*.bmp)"));
    if(!fileName.isNull())
    {
        originalPixmap.copy(screenRect).save(fileName);
        this->hide();
    }
    rectangle.setRect(0,0,0,0);
}

void Srceen::MenuClose()
{
    rectangle.setRect(0,0,0,0);
    this->close();
}

void Srceen::SrceenValInit()
{
    saveSreenShot = new QAction(tr("保存截图"), this);
    connect(saveSreenShot, SIGNAL(triggered()), this, SLOT(SaveSrceenShot()));
    quitSreenShot = new QAction(tr("退出截图"), this);
    connect(quitSreenShot, SIGNAL(triggered()), this, SLOT(MenuClose()));
    saveCopyAs = new QAction(tr("另存为"),this);
    connect(saveCopyAs, SIGNAL(triggered()), this, SLOT(SaveCopyAs()));
    RightButtonMenu = new QMenu(this);
}
