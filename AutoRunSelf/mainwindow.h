#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QButtonGroup>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void slot_CheckButton_checket(int);

private:
    void write_ini();
    void read_ini();
    void SetAutoRun(bool isAutoRun);//是否开机启动
private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;

    /*CheckBox*/
    QButtonGroup* setting;
};

#endif // MAINWINDOW_H
