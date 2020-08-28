#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void checkMyThread();
private slots:
    void RecvVal(int Val);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QThread m_thread;
    MyThread m_ProgressBarVal;
};

#endif // MAINWINDOW_H
