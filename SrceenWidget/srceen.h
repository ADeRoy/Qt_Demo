#ifndef SRCEEN_H
#define SRCEEN_H

#include <QMenu>
#include <QMouseEvent>
#include <QScreen>
#include <QWidget>
#include <QApplication>
#include <QClipboard>

class Srceen : public QWidget
{
    Q_OBJECT
public:
    explicit Srceen(QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent *);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);    //右键菜单
public slots:
    void GetWindowSrceen(); //获取桌面全屏
    void SaveSrceenShot();  //保存截屏
    void SaveCopyAs();
    void MenuClose();
private:
    void SrceenValInit();
private:
    QScreen *screen;        //桌面截图
    QPixmap originalPixmap; //截图
    QRect rectangle;        //截图矩形
    QRect screenRect;       //屏幕截图矩形
    QRect enlargeRect;      //放大矩形
    QPoint mousePos;        //鼠标坐标

    QClipboard * clip;      //剪切板

    QMenu *RightButtonMenu; //右键菜单
    QAction *saveSreenShot; //保存到粘贴板
    QAction *saveCopyAs;    //另存为
    QAction *quitSreenShot; //退出截图
};

#endif // SRCEEN_H
